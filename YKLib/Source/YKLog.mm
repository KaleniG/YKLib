#include "YKLog.h"

#if defined(PLATFORM_MACOS)
#import <Cocoa/Cocoa.h>
#endif

namespace yk
{
  void LogRuntimeError(const std::string& message)
  {
#if defined(PLATFORM_MACOS)
    NSString *nsMessage = [NSString stringWithUTF8String:message.c_str()];
    
    dispatch_async(dispatch_get_main_queue(), ^{
      NSAlert *alert = [[NSAlert alloc] init];
      [alert setMessageText:@"Runtime Error"];
      [alert setInformativeText:nsMessage];
      [alert addButtonWithTitle:@"OK"];
      [alert setAlertStyle:NSAlertStyleCritical];
      [alert runModal];
    });
#endif
  }
}
