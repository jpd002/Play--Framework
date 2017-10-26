#import <Foundation/Foundation.h>
#include "http/AppleHttpClient.h"

using namespace Framework;
using namespace Framework::Http;

RequestResult CAppleHttpClient::SendRequest()
{
	NSURLSessionConfiguration* sessionConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
	NSURLSession* session = [NSURLSession sessionWithConfiguration: sessionConfig];
	
	NSURL* url = [NSURL URLWithString: [NSString stringWithUTF8String: m_url.c_str()]];
	NSURLRequest* request = [NSURLRequest requestWithURL: url];
	auto waitSema = dispatch_semaphore_create(0);
	__block RequestResult result;
	__block NSError* requestError = nil;
	
	auto completionHandler =
		^(NSData* data, NSURLResponse* response, NSError* error)
		{
			requestError = [error retain];
			if(!error)
			{
				NSHTTPURLResponse* httpResponse = (NSHTTPURLResponse*)response;
				result.statusCode = static_cast<HTTP_STATUS_CODE>([httpResponse statusCode]);
				result.data.Write([data bytes], [data length]);
				result.data.Seek(0, Framework::STREAM_SEEK_SET);
			}
			dispatch_semaphore_signal(waitSema);
		};
	NSURLSessionDataTask* dataTask = [session dataTaskWithRequest: request completionHandler: completionHandler];
	[dataTask resume];
	
	dispatch_semaphore_wait(waitSema, DISPATCH_TIME_FOREVER);
	dispatch_release(waitSema);
	
	if(requestError)
	{
		[requestError release];
		throw std::runtime_error("Failed to execute request");
	}
	
	return result;
}
