/* $Id: zufall.h,v 1.15 2001/11/09 12:43:45 thoma Exp $ */
/*  Midgard Character Generator
 *  Copyright (C) 2001 Malte Thoma
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//#include <iomanip.h>
//#include <time.h>
//#include <limits.h>
#include <stdlib.h>

class Random {
public:
//        Random(long seed=0) { _seed =( seed ? seed : time(NULL) ); }
//        void seed(long seed=0)   { _seed =( seed ? seed : time(NULL) ); }
//        int integer() { return _next(); }
        int integer(int min, int max) {return min + int(((max-min+1.)*rand())/(RAND_MAX+1.0)); }
//        int integer(int min, int max) {return min+ (int)(10 * rand()/(RAND_MAX)); }
//        double real() {return double(_next())/double(INT_MAX); }
//        double real() {return double(rand())/double(RAND_MAX); }
//        int integer(int min, int max) {return min+_next()%(max-min+1); }
/*
private:
        unsigned long _seed;
        void _randomize() { _seed = (314159265*_seed + 13579) % ULONG_MAX;}
        int _next()
         { int iterations = _seed % 3;
           for (int i=0;i<= iterations; ++i) _randomize(); 
           return int(_seed/2);
         }
*/
};
