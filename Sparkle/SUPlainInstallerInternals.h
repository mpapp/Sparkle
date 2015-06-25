//
//  SUPlainInstallerInternals.m
//  Sparkle
//
//  Created by Andy Matuschak on 3/9/06.
//  Copyright 2006 Andy Matuschak. All rights reserved.
//

#ifndef SUPLAININSTALLERINTERNALS_H
#define SUPLAININSTALLERINTERNALS_H

#import <Foundation/Foundation.h>

#import "SUPlainInstaller.h"

@interface SUPlainInstaller (MMExtendedAttributes)
// Removes the directory tree rooted at |root| from the file quarantine.
// The quarantine was introduced on OS X 10.5 and is described at:
//
//   http://developer.apple.com/releasenotes/Carbon/RN-LaunchServices/index.html
//#apple_ref/doc/uid/TP40001369-DontLinkElementID_2
//
// If |root| is not a directory, then it alone is removed from the quarantine.
// Symbolic links, including |root| if it is a symbolic link, will not be
// traversed.
//
// Ordinarily, the quarantine is managed by calling LSSetItemAttribute
// to set the kLSItemQuarantineProperties attribute to a dictionary specifying
// the quarantine properties to be applied.  However, it does not appear to be
// possible to remove an item from the quarantine directly through any public
// Launch Services calls.  Instead, this method takes advantage of the fact
// that the quarantine is implemented in part by setting an extended attribute,
// "com.apple.quarantine", on affected files.  Removing this attribute is
// sufficient to remove files from the quarantine.
+ (void)releaseFromQuarantine:(NSString *)root;
@end

@interface SUPlainInstaller (Internals)
+ (NSString *)temporaryNameForPath:(NSString *)path;
+ (BOOL)copyPathWithAuthentication:(NSString *)src overPath:(NSString *)dst temporaryName:(NSString *)tmp error:(NSError **)error;
+ (void)_movePathToTrash:(NSString *)path;
+ (BOOL)_removeFileAtPath:(NSString *)path error:(NSError **)error;
+ (BOOL)_removeFileAtPathWithForcedAuthentication:(NSString *)src error:(NSError **)error;
@end

#endif
