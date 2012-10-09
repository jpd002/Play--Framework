#ifndef _LZARI_H_
#define _LZARI_H_

#include <stdio.h>
#include "Types.h"
#include "Stream.h"

namespace Framework
{
	class CLzAri
	{
	public:
		static void		Compress(Framework::CStream& dst, Framework::CStream& src);
		static void		Decompress(Framework::CStream& dst, Framework::CStream& src);

	private:
		enum
		{
			N			= 4096,		/* size of ring buffer */
			F			= 60,		/* upper limit for match_length */
			THRESHOLD	= 2,		/* encode string into position and length
									   if match_length is greater than this */
			NIL			= N,		/* index for root of binary search trees */

			M			= 15,

			/*	Q1 (= 2 to the M) must be sufficiently large, but not so
			large as the unsigned long 4 * Q1 * (Q1 - 1) overflows.  */

			Q1			= (1UL << M),
			Q2			= (2 * Q1),
			Q3			= (3 * Q1),
			Q4			= (4 * Q1),
			MAX_CUM		= (Q1 - 1),

			N_CHAR		= (256 - THRESHOLD + F) /* character code = 0, 1, ..., N_CHAR - 1 */
		};

								CLzAri();
		virtual					~CLzAri();

		void					PutBit(int);
		void					FlushBitBuffer();
		int						GetBit();

		void					InitTree();
		void					InsertNode(int);
		void					DeleteNode(int);

		void					StartModel();
		void					UpdateModel(int);

		void					Output(int);

		void					EncodeChar(int);
		void					EncodePosition(int);
		void					EncodeEnd();

		int						BsrcSym(unsigned int);
		int						BsrcPos(unsigned int);

		void					StartDecode();
		int						DecodeChar();
		int						DecodePosition();

		void					Encode();
		void					Decode();

		unsigned char			text_buf[N + F - 1];	/* ring buffer of size N, with extra F-1 bytes to facilitate string comparison */
		int						match_position, match_length;  /* of longest match.  These are set by the InsertNode() procedure. */
		int						lson[N + 1], rson[N + 257], dad[N + 1];  /* left & right children & parents -- These constitute binary search trees. */

		uint32					low, high, value;
		int						shifts;					/* counts for magnifying low and high around Q2 */
		int						char_to_sym[N_CHAR], sym_to_char[N_CHAR + 1];
		unsigned int			sym_freq[N_CHAR + 1];	/* frequency for symbols */
		unsigned int			sym_cum[N_CHAR + 1];	/* cumulative freq for symbols */
		unsigned int			position_cum[N + 1];	/* cumulative freq for positions */

		Framework::CStream*		inputStream;
		Framework::CStream*		outputStream;

		unsigned int			putBuffer;
		unsigned int			putMask;
		unsigned int			getBuffer;
		unsigned int			getMask;
	};
}

#endif
