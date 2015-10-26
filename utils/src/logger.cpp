#include <mutex>
#include <fstream>
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>

#include "hypha/utils/logger.h"

using Poco::FileChannel;
using Poco::SplitterChannel;
using Poco::ConsoleChannel;
using Poco::AutoPtr;
using Poco::FormattingChannel;
using Poco::PatternFormatter;

using namespace hypha::utils;

Logger *Logger::singleton = 0;

Logger *Logger::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();
        if (!singleton) {
            singleton = new Logger();
        }
        mutex.unlock();
    }
    return singleton;
}

void Logger::info(std::string message) {
    instance();
    static std::mutex mutex;
    mutex.lock();
    Poco::Logger &logger = Poco::Logger::get("[info]");
    logger.information(message);
    mutex.unlock();
}

void Logger::warning(std::string message) {
    instance();
    static std::mutex mutex;
    mutex.lock();
    Poco::Logger &logger = Poco::Logger::get("[warning]");
    logger.warning(message);
    mutex.unlock();
}

void Logger::error(std::string message) {
    instance();
    static std::mutex mutex;
    mutex.lock();
    Poco::Logger &logger = Poco::Logger::get("[error]");
    logger.error(message);
    mutex.unlock();
}

void Logger::fatal(std::string message) {
    instance();
    static std::mutex mutex;
    mutex.lock();
    Poco::Logger &logger = Poco::Logger::get("[fatal]");
    logger.fatal(message);
    mutex.unlock();
}

Logger::Logger() {
    init();
}

Logger::~Logger() {

}

void Logger::init() {
    AutoPtr<ConsoleChannel> pCons(new ConsoleChannel);
    AutoPtr<FileChannel> pFile(new FileChannel);
    pFile->setProperty("path", "hypha.log");
    pFile->setProperty("rotation", "1 M");
    pFile->setProperty("archive", "timestamp");
    pFile->setProperty("purgeCount", "10");
    AutoPtr<SplitterChannel> pSplitter(new SplitterChannel);
    pSplitter->addChannel(pCons);
    pSplitter->addChannel(pFile);
    AutoPtr<PatternFormatter> pPF(new PatternFormatter);
    pPF->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pSplitter));
    Poco::Logger::root().setChannel(pFC);
}

