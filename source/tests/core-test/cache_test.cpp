// Copyright (c) 2016 Hypha

#include <gmock/gmock.h>
#include <hypha/core/cache/cache.h>

class cache_test : public testing::Test {
 public:
};

TEST_F(cache_test, CheckSomeResults) {
  hypha::cache::Cache cache;
  ASSERT_TRUE(cache.connect());
  std::string testkey = "testkey";
  std::string testvalue = "testvalue";
  cache.put(testkey, testvalue);
  ASSERT_TRUE(cache.getRaw(testkey) == testvalue);

  std::string testdata = "testdata";
  testkey = cache.put(testdata);
  ASSERT_TRUE(testdata == cache.get(testkey));
  std::cout << testkey << "  " << testdata << std::endl;

  testkey = "localhost:1234";
  ASSERT_TRUE("localhost" == hypha::cache::Cache::getHostname(testkey));
  ASSERT_TRUE("1234" == hypha::cache::Cache::getUUID(testkey));
}
