/*
 * Phasor.h
 *
 * Copyright 2012 Tim Barrass.
 *
 * This file is part of Mozzi.
 *
 * Mozzi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mozzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mozzi.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PHASOR_H_
#define PHASOR_H_

#include "Arduino.h"

/** Phasor repeatedly generates a ramp at a set frequency.
The output of Phasor.next() is an unsigned number between 0 and the maximum that can be expressed by the template parameter number type T.
@tparam T the type of numbers to use. For example, Phasor <unsigned int> myline; makes a
Phasor which uses unsigned ints.
*/

template <class T, unsigned int UPDATE_RATE>
class Phasor
{
private:
	T current_value;
	T step_size;
	T MAX_VALUE;

public:
	/** Constructor. Use the template parameter to set the type of numbers you
	want to use. For example, Phasor <unsigned int> myphasor; makes a Phasor which uses unsigned ints and counts from 0 to 65535.
	 */
	Phasor ():MAX_VALUE((T)-1)
	{
		;
	}

	/** Increments one step along the phase.
	@return the next value.
	 */
	inline
	T next()
	{
		current_value += step_size; // will wrap
		return current_value;
	}

	/** Set the current value of the phasor. The Phasor will continue incrementing from this
	value using any previously calculated step size.
	 */
	inline
	void set(T value)
	{
		current_value=value;
	}

	/** Given a target value and the number of steps to take on the way, this calculates
	the step size needed to get there from the current value.
	 */
	inline
	void setFreq(int f)
	{
		step_size=(T)(((float)(targetvalue-current_value)/num_steps));

	}


	/** Set the Phasor frequency with a float. Using a float is the most reliable
	way to set frequencies, -Might- be slower than using an int but you need either
	this, setFreq_Q24n8() or setFreq_Q16n16() for fractional frequencies.
	@param frequency is  how many times per second to count from 0 to maximum.
	 */
	inline
	void setFreq(float frequency)
	{ // 1 us - using float doesn't seem to incur measurable overhead with the oscilloscope
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			step_size = (T)(((float)MAX_VALUE * frequency)/UPDATE_RATE);
		}
	}
};

#endif /* PHASOR_H_ */

