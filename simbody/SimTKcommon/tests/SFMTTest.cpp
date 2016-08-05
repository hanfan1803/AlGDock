/* -------------------------------------------------------------------------- *
 *                       Simbody(tm): SimTKcommon                             *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK biosimulation toolkit originating from           *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org/home/simbody.  *
 *                                                                            *
 * Portions copyright (c) 2007-12 Stanford University and the Authors.        *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

#include "../../Random/src/SFMT.h"

#include <cassert>
#include <iostream>
using namespace SimTK_SFMT;
using std::cout;
using std::endl;

int main() {
    try {
    	SFMTData* sfmt = createSFMTData();
    	
    	// Read off the first five numbers generated by SFMT, and compare them to the expected values provided with the library.
    	
    	init_gen_rand(1234, *sfmt);
    	unsigned int expected[] = {3440181298u, 1564997079u, 1510669302u, 2930277156u, 1452439940u};
    	for (int i = 0; i < 5; ++i)
    		assert(gen_rand32(*sfmt) == expected[i]);
    	
    	// Make sure that getting numbers a whole array at a time gives the same values.
    	
    	int length = get_min_array_size32();
    	if (length < 5)
    		length = 5;
    	uint32_t* values = new uint32_t[length];
    	init_gen_rand(1234, *sfmt);
    	fill_array32(values, length, *sfmt);
    	for (int i = 0; i < 5; ++i)
    		assert(values[i] == expected[i]);
    	deleteSFMTData(sfmt);
    	delete[] values;
    } catch(const std::exception& e) {
        cout << "exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}

