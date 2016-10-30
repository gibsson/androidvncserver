AndroidVNCServer
================

This source code has been extracted from oNaiPs droidvncserver project:
https://github.com/oNaiPs/droidVncServer

This repo however only contains the daemon source code. It is meant to be included inside an AOSP source tree and there leverages all the libraries already present:
- libvncserver
- libssl / libcrypto (BoringSSL)
- libpng
- libjpeg

*Note*: the flinger screen method doesn't seem to work properly, it is therefore preferred to use the fb approach:

```# droidvncserver -m fb```

**LICENSE: LGPLv3+**
