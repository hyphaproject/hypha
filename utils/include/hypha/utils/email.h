#ifndef EMAIL_H
#define EMAIL_H

#include "../utils.h"
#include <string>
namespace hypha {
namespace utils {
class Utils_API EMail {
  public:
    EMail();
    void setHost(std::string host);
    void setPort(int port);
    void setUser(std::string user);
    void setPassword(std::string password);
    bool sendMessage(std::string to, std::string subject, std::string content);
    bool sendMessageWithAttachment(std::string to, std::string subject, std::string content, std::string filename, std::string file);

  protected:
    std::string host;
    int port;
    std::string user;
    std::string password;

};
}
}
#endif // EMAIL_H
