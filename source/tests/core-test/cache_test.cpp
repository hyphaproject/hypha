// Copyright (c) 2016 Hypha

#include <hypha/core/cache/cache.h>
#include <gmock/gmock.h>

class cache_test : public testing::Test {
 public:
};

TEST_F(cache_test, CheckSomeResults) {
    hypha::cache::Cache cache;
    ASSERT_TRUE(cache.connect());
    std::string testkey = "testkey";
    std::string testvalue = "testvalue";
    cache.put(testkey, testvalue);
    ASSERT_TRUE(cache.get(testkey) == testvalue);
}
