//
//  RMFoundation.c
//
// Copyright (c) 2008-2009, Route-Me Contributors
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#import "RMFoundation.h"
#import <math.h>

bool RMProjectedPointEqualToProjectedPoint(RMProjectedPoint point1, RMProjectedPoint point2)
{
	return point1.x == point2.x && point2.y == point2.y;
}

bool RMProjectedRectIntersectsProjectedRect(RMProjectedRect rect1, RMProjectedRect rect2)
{
	double minX1 = rect1.origin.x;
	double maxX1 = rect1.origin.x + rect1.size.width;
	double minY1 = rect1.origin.y;
	double maxY1 = rect1.origin.y + rect1.size.height;

	double minX2 = rect2.origin.x;
	double maxX2 = rect2.origin.x + rect2.size.width;
	double minY2 = rect2.origin.y;
	double maxY2 = rect2.origin.y + rect2.size.height;

	return ((minX1 <= minX2 && minX2 <= maxX1) || (minX2 <= minX1 && minX1 <= maxX2))
		&& ((minY1 <= minY2 && minY2 <= maxY1) || (minY2 <= minY1 && minY1 <= maxY2));
}

bool RMProjectedRectContainsProjectedRect(RMProjectedRect rect1, RMProjectedRect rect2)
{
	double minX1 = rect1.origin.x;
	double maxX1 = rect1.origin.x + rect1.size.width;
	double minY1 = rect1.origin.y;
	double maxY1 = rect1.origin.y + rect1.size.height;

	double minX2 = rect2.origin.x;
	double maxX2 = rect2.origin.x + rect2.size.width;
	double minY2 = rect2.origin.y;
	double maxY2 = rect2.origin.y + rect2.size.height;

    return ((minX2 >= minX1 && maxX2 <= maxX1) && (minY2 >= minY1 && maxY2 <= maxY1));
}

RMProjectedPoint RMScaleProjectedPointAboutPoint(RMProjectedPoint point, float factor, RMProjectedPoint pivot)
{
	point.x = (point.x - pivot.x) * factor + pivot.x;
	point.y = (point.y - pivot.y) * factor + pivot.y;

	return point;
}

RMProjectedRect RMScaleProjectedRectAboutPoint(RMProjectedRect rect, float factor, RMProjectedPoint pivot)
{
	rect.origin = RMScaleProjectedPointAboutPoint(rect.origin, factor, pivot);
	rect.size.width *= factor;
	rect.size.height *= factor;

	return rect;
}

RMProjectedPoint RMTranslateProjectedPointBy(RMProjectedPoint point, RMProjectedSize delta)
{
	point.x += delta.width;
	point.y += delta.height;

	return point;
}

RMProjectedRect RMTranslateProjectedRectBy(RMProjectedRect rect,  RMProjectedSize delta)
{
	rect.origin = RMTranslateProjectedPointBy(rect.origin, delta);

	return rect;
}

RMProjectedPoint RMProjectedPointMake(double x, double y)
{
	RMProjectedPoint point = { x, y };

	return point;
}

RMProjectedRect RMProjectedRectMake(double x, double y, double width, double height)
{
	RMProjectedRect rect = {
		{x, y},
		{width, height}
	};

	return rect;
}

RMProjectedSize RMProjectedSizeMake(double width, double heigth)
{
    RMProjectedSize size = {
        width, heigth
    };

    return size;
}

RMProjectedRect RMProjectedRectZero()
{
    return RMProjectedRectMake(0.0, 0.0, 0.0, 0.0);
}

double RMEuclideanDistanceBetweenProjectedPoints(RMProjectedPoint point1, RMProjectedPoint point2)
{
    double xd = point2.x - point1.x;
	double yd = point2.y - point1.y;

	return sqrt(xd*xd + yd*yd);
}
