#import <Foundation/Foundation.h>
#include "http/AppleHttpClient.h"

using namespace Framework;
using namespace Framework::Http;

RequestResult CAppleHttpClient::SendRequest()
{
	NSURLSessionConfiguration* sessionConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
	NSURLSession* session = [NSURLSession sessionWithConfiguration: sessionConfig];
	
	NSURL* url = [NSURL URLWithString: [NSString stringWithUTF8String: m_url.c_str()]];
	NSMutableURLRequest* request = [NSMutableURLRequest requestWithURL: url];
	
	switch(m_verb)
	{
	default:
		assert(false);
	case HTTP_VERB::GET:
		[request setHTTPMethod: @"GET"];
		break;
	case HTTP_VERB::HEAD:
		[request setHTTPMethod: @"HEAD"];
		break;
	case HTTP_VERB::POST:
		[request setHTTPMethod: @"POST"];
		break;
	case HTTP_VERB::PUT:
		[request setHTTPMethod: @"PUT"];
		break;
	}
	
	for(const auto& header : m_headers)
	{
		NSString* key = [NSString stringWithUTF8String: header.first.c_str()];
		NSString* value = [NSString stringWithUTF8String: header.second.c_str()];
		[request setValue: value forHTTPHeaderField: key];
	}
	
	if(!m_requestBody.empty())
	{
		NSData* bodyData = [NSData dataWithBytes: m_requestBody.data() length: m_requestBody.size()];
		[request setHTTPBody: bodyData];
	}
	
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
				
				for(NSString* key in httpResponse.allHeaderFields)
				{
					NSString* value = [httpResponse.allHeaderFields valueForKey: key];
					result.headers.insert(std::make_pair([key UTF8String], [value UTF8String]));
				}
				
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
