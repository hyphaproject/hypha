// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/utils/utils_api.h>
#include <string>

namespace hypha {
namespace utils {
/** EMail Class supports sending emails with file attachment.
 * The EMail must given a serverhost, the port, username and password.
 * Then there can be send a message with or without attachment.
 */
class UTILS_API EMail {
 public:
  EMail();
  void setHost(std::string host);
  void setPort(int port);
  void setUser(std::string user);
  void setPassword(std::string password);
  bool sendMessage(std::string to, std::string subject, std::string content);
  bool sendMessageWithAttachment(std::string to, std::string subject,
                                 std::string content, std::string filename,
                                 std::string file);

 protected:
  std::string host;
  int port;
  std::string user;
  std::string password;
};
}
}
