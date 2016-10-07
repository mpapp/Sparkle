//
//  main.m
//  verify-dsa
//
//  Created by Matias Piipari on 07/10/2016.
//  Copyright © 2016 Sparkle Project. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SUDSAVerifier.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        if (argc != 4) {
            fputs("Expecting three arguments: [archive-path] [public-key-path] [base64-encoded-signature]", stderr);
            return -1;
        }
        
        NSString *archivePath = [NSString stringWithUTF8String:argv[1]];
        NSString *publicKeyPath = [NSString stringWithUTF8String:argv[2]];
        NSString *signature = [NSString stringWithUTF8String:argv[3]];
        
        NSError *err = nil;
        NSString *publicKey = [NSString stringWithContentsOfFile:publicKeyPath
                                                        encoding:NSUTF8StringEncoding
                                                           error:&err];
        
        if (!publicKey) {
            fputs([NSString stringWithFormat:@"Invalid signature:\n%@", err].UTF8String, stderr);
            return -2;
        }
        
        if (![SUDSAVerifier validatePath:archivePath
                 withEncodedDSASignature:signature
                        withPublicDSAKey:publicKey]) {
            fputs("Invalid signature", stderr);
            return -3;
        }
        else {
            fputs("ok", stdout);
            return 0;
        }
    }
}
