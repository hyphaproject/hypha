// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/core_api.h>
#include <hypha/core/exceptions/hyphaexception.h>

namespace hypha {
namespace exceptions {

class CORE_API ConfigFileNotFound : public HyphaException {
 public:
  virtual const char* what() const throw() {
    return "Config file could not been found!";
  }
};
}  // namespace exceptions
}  // namespace hypha
