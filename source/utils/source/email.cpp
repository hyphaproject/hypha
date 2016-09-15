#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SMTPClientSession.h>
#include <hypha/utils/email.h>
#include <iostream>
#include <string>

using namespace hypha::utils;

EMail::EMail() { this->port = 25; }

void EMail::setHost(std::string host) { this->host = host; }

void EMail::setPort(int port) { this->port = port; }

void EMail::setUser(std::string user) { this->user = user; }

void EMail::setPassword(std::string password) { this->password = password; }

bool EMail::sendMessage(std::string to, std::string subject,
                        std::string content) {
  subject = Poco::Net::MailMessage::encodeWord(subject, "UTF-8");
  Poco::Net::MailMessage message;
  message.setSender(this->user);
  message.addRecipient(Poco::Net::MailRecipient(
      Poco::Net::MailRecipient::PRIMARY_RECIPIENT, to));
  message.setSubject(subject);
  message.setContentType("text/plain; charset=UTF-8");
  message.setContent(content, Poco::Net::MailMessage::ENCODING_8BIT);
  try {
    Poco::Net::SMTPClientSession session(host, port);
    session.open();
    try {
      session.login(Poco::Net::SMTPClientSession::AUTH_NONE, user, password);
      session.sendMessage(message);
      std::cout << "Message successfully sent" << std::endl;
      session.close();
    } catch (Poco::Net::SMTPException &e) {
      std::cerr << e.displayText() << std::endl;
      session.close();
      return 0;
    }
  } catch (Poco::Net::NetException &e) {
    std::cerr << e.displayText() << std::endl;
    return 0;
  }
  return true;
}

bool EMail::sendMessageWithAttachment(std::string to, std::string subject,
                                      std::string content, std::string filename,
                                      std::string file) {
  subject = Poco::Net::MailMessage::encodeWord(subject, "UTF-8");
  Poco::Net::MailMessage message;
  message.setSender(this->user);
  message.addRecipient(Poco::Net::MailRecipient(
      Poco::Net::MailRecipient::PRIMARY_RECIPIENT, to));
  message.setSubject(subject);
  message.setContentType("text/plain; charset=UTF-8");
  message.setContent(content, Poco::Net::MailMessage::ENCODING_8BIT);

  message.addAttachment(filename, new Poco::Net::FilePartSource(file));

  try {
    Poco::Net::SMTPClientSession session(host, port);
    session.open();
    try {
      session.login(Poco::Net::SMTPClientSession::AUTH_NONE, user, password);
      session.sendMessage(message);
      std::cout << "Message successfully sent" << std::endl;
      session.close();
    } catch (Poco::Net::SMTPException &e) {
      std::cerr << e.displayText() << std::endl;
      session.close();
      return 0;
    }
  } catch (Poco::Net::NetException &e) {
    std::cerr << e.displayText() << std::endl;
    return 0;
  }
  return true;
}
