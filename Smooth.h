/*
 * Smooth.h
 *
 * Copyright 2012 Tim Barrass.
 *
 * This file is part of Cuttlefish.
 *
 * Cuttlefish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cuttlefish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cuttlefish.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SMOOTH_H_
#define SMOOTH_H_

#include "Arduino.h"

/** A simple low pass filter for smoothing control signals. This algorithm comes
from http://en.wikipedia.org/wiki/Low-pass_filter: y[i] := y[i-1] + α * (x[i] -
y[i-1]), translated as out = last_out + a * (in - last_out). It's not calibrated
to any real-world update rate, so if you use it at CONTROL_RATE and you change
CONTROL_RATE, you'll need to adjust the smoothness value to suit.
 */

template <class numType>
class Smooth
{
private:
	numType last_out;
	float a;

public:
	/** Instantiates a Smooth. Use the template parameter to set the type of numbers you
	want to use. For example, Smooth <int> mySmooth; makes a Smooth which works with
	ints. The smoothness parameter sets how much smoothing the filter will apply to
	its input. Use a float in the range 0~1, where 0 is not very smooth and 0.99 is
	very smooth;
	 */
	Smooth(float smoothness): a(1.f-smoothness)
	{
		;
	}

	/** Filters the input and returns the filtered value.
	 */
	inline
	numType next(numType in)
	{
		numType out = (numType)((a * (in - last_out)) + last_out);
		last_out = out;
		return out;
	}

	/** Sets how much smoothing the filter will apply to its input. Use a float in the
	range 0~1, where 0 is not very smooth and 0.99 is very smooth;
	 */
	inline
	void setSmoothness(float value)
	{
		a=1.f-value;
	}

};

#endif /* SMOOTH_H_ */