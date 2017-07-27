/*
 * droid vnc server - Android VNC server
 * Copyright (C) 2011 Jose Pereira <onaips@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "common.h"
#include "flinger.h"
#include "screenFormat.h"

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IMemory.h>
#include <gui/ISurfaceComposer.h>
#include <gui/SurfaceComposerClient.h>

using namespace android;

extern screenFormat screenformat;

ScreenshotClient *screenshotClient = NULL;
sp<IBinder> display = NULL;

extern "C" screenFormat getScreenFormatFlinger(void)
{
	// Get format on PixelFormat struct
	PixelFormat f = screenshotClient->getFormat();

	screenFormat format;

	format.bitsPerPixel = bitsPerPixel(f);
	format.width = screenshotClient->getWidth();
	format.height = screenshotClient->getHeight();
	format.size = format.bitsPerPixel*format.width*format.height/CHAR_BIT;
	// TODO: remove hardcoded values
	format.redShift = 0;
	format.redMax = 8;
	format.greenShift = 8;
	format.greenMax = 8;
	format.blueShift = 16;
	format.blueMax = 8;
	format.alphaShift = 24;
	format.alphaMax = 8;

	return format;
}

extern "C" int initFlinger(void)
{
	int err;

	screenshotClient = new ScreenshotClient();

	// TODO: fixing diplayId to 0 for now
	display = SurfaceComposerClient::getBuiltInDisplay(0);
	if (display == NULL) {
		L("Couldn't getBuiltInDisplay\n");
		return -1;
	}

	err = screenshotClient->update(display, Rect(), true);
	if (err != NO_ERROR) {
		L("screenshotClient->update %d\n", err);
		return -1;
	}

	if (!screenshotClient->getPixels()) {
		L("Couldn't getPixels\n");
		return -1;
	}

	screenformat = getScreenFormatFlinger();
	if (screenformat.width <= 0) {
		L("Received a bad screen size from flinger.\n");
	}

	return 0;
}

extern "C" void closeFlinger(void)
{
	free(screenshotClient);
}

extern "C" unsigned char *readBufferFlinger(void)
{
	screenshotClient->update(display, Rect(), true);
	return (unsigned char*)screenshotClient->getPixels();
}

