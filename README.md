# Hypha libraries
[![Build Status][travis-image]][travis]
[![Coverage_Status][coveralls-image]][coveralls]
[![Documentation][codedocs-image]][codedocs]
[![Gitter][gitter-image]][gitter]

[travis-image]: https://travis-ci.org/hyphaproject/hypha.png?branch=master
[travis]: http://travis-ci.org/hyphaproject/hypha

[coveralls-image]: https://img.shields.io/coveralls/hyphaproject/hypha.svg?label=Coverage
[coveralls]: https://coveralls.io/github/hyphaproject/hypha

[codedocs-image]: https://codedocs.xyz/hyphaproject/hypha.svg
[codedocs]: https://codedocs.xyz/hyphaproject/hypha

[gitter-image]: https://badges.gitter.im/Join%20Chat.svg
[gitter]: https://gitter.im/hyphaproject/public

### Quick start

First install CMake, Poco, Boost

Then build and run.

```sh
git clone https://github.com/hyphaproject/hypha
cd hypha
mkdir build
cd build
cmake ..
cmake --build .
```

## For Developer

run tests:
```sh
cmake -DOPTION_BUILD_TESTS=1 ..
make
./hyphacore-test
```

run clang-format:
```sh
make clang-format
```

run clang-tidy:
```sh
make clang-tidy
```

run coverage:
```sh
cmake -DOPTION_BUILD_TESTS=1 -DCMAKE_BUILD_TYPE=Coverage ..
make hyphacore-test_coverage
```

open coverate/index.html

-------------------------------
[Logo](/deploy/images/logo.png) Icon made by [Freepik](http://www.freepik.com) from [www.flaticon.com](http://www.flaticon.com)
