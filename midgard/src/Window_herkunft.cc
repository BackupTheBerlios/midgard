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

/* Processed by ecpg (2.8.0) */
/* These three include files are added by the preprocessor */
#include <ecpgtype.h>
#include <ecpglib.h>
#include <ecpgerrno.h>
#line 1 "Window_herkunft.pgcc"


#include "config.h"
#include "Window_herkunft.hh"
#include "midgard_CG.hh"
#include <Gtk_OStream.h>

#line 1 "/usr/include/postgresql/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#define SQLERRMC_LEN	70

#ifdef __cplusplus
extern		"C"
{
#endif

	struct sqlca
	{
		char		sqlcaid[8];
		long		sqlabc;
		long		sqlcode;
		struct
		{
			int			sqlerrml;
			char		sqlerrmc[SQLERRMC_LEN];
		}			sqlerrm;
		char		sqlerrp[8];
		long		sqlerrd[6];
		/* Element 0: empty						*/
		/* 1: OID of processed tuple if applicable			*/
		/* 2: number of rows processed				*/
		/* after an INSERT, UPDATE or 				*/
		/* DELETE statement					*/
		/* 3: empty						*/
		/* 4: empty						*/
		/* 5: empty						*/
		char		sqlwarn[8];
		/* Element 0: set to 'W' if at least one other is 'W' 	*/
		/* 1: if 'W' at least one character string	  	*/
		/* value was truncated when it was		   	*/
		/* stored into a host variable.			   	*/
		/* 2: if 'W' a (hopefully) non-fatal notice occured 	*/		/* 3: empty									  */
		/* 4: empty						*/
		/* 5: empty						*/
		/* 6: empty						*/
		/* 7: empty						*/

		char		sqlext[8];
	};

	extern struct sqlca sqlca;


#ifdef __cplusplus
}
#endif

#endif

#line 11 "Window_herkunft.pgcc"

#include <Aux/Transaction.h>
#include <Aux/SQLerror.h>

void Window_herkunft::on_clist_herkunftsland_select_row(gint row, gint column, GdkEvent *event)
{   
   string land = clist_herkunftsland->get_text(row,1);
   hauptfenster->herkunft_uebernehmen(land);
   destroy();
}

Window_herkunft::Window_herkunft(midgard_CG* h)
{
 hauptfenster=h;
 /* exec sql begin declare section */
    
 
#line 26 "Window_herkunft.pgcc"
   char  db_land [ 50 ]   ,  db_kontinent [ 50 ]   ;
/* exec sql end declare section */
#line 27 "Window_herkunft.pgcc"

 Gtk::OStream os(clist_herkunftsland);
 Transaction tr;
 
/* declare ein  cursor for select distinct kontinent  , land   from sprachen    */
#line 31 "Window_herkunft.pgcc"

 { ECPGdo(__LINE__, NULL, "declare ein  cursor for select distinct kontinent  , land   from sprachen   ", ECPGt_EOIT, ECPGt_EORT);}
#line 32 "Window_herkunft.pgcc"

 SQLerror::test(__FILELINE__);
 while (true)
  {
    { ECPGdo(__LINE__, NULL, "fetch ein", ECPGt_EOIT, 
	ECPGt_char,(db_kontinent),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_land),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 36 "Window_herkunft.pgcc"

    SQLerror::test(__FILELINE__,100);
    if (sqlca.sqlcode) break;
    os << db_kontinent<<"\t"<<db_land<<"\n";
  }   
 tr.close();
 { ECPGdo(__LINE__, NULL, "close ein", ECPGt_EOIT, ECPGt_EORT);}
#line 42 "Window_herkunft.pgcc"

}