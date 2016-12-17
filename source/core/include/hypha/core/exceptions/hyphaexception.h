// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/core_api.h>

#include <exception>

namespace hypha {
namespace exceptions {

class CORE_API HyphaException : public std::exception {
 public:
  virtual const char* what() const throw() {
    return "Unknown Hypha Exception!";
  }
};
}  // namespace exceptions
}  // namespace hypha
