/* Processed by ecpg (2.9.0) */
/* These three include files are added by the preprocessor */
#include <ecpgtype.h>
#include <ecpglib.h>
#include <ecpgerrno.h>
#line 1 "Ruestung.pgcc"
#include "Ruestung.hh"
#include <Aux/SQLerror.h>
#include <Aux/Transaction.h>

#line 1 "/usr/local/pgsql/include/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef DLLIMPORT
#ifdef __CYGWIN__
#define DLLIMPORT __declspec (dllimport)
#else
#define DLLIMPORT
#endif /* __CYGWIN__ */
#endif /* DLLIMPORT */

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
		/* after an INSERT, UPDATE or				*/
		/* DELETE statement					*/
		/* 3: empty						*/
		/* 4: empty						*/
		/* 5: empty						*/
		char		sqlwarn[8];
		/* Element 0: set to 'W' if at least one other is 'W'	*/
		/* 1: if 'W' at least one character string		*/
		/* value was truncated when it was			*/
		/* stored into a host variable.				*/

		/*
		 * 2: if 'W' a (hopefully) non-fatal notice occured
		 *//* 3: empty */
		/* 4: empty						*/
		/* 5: empty						*/
		/* 6: empty						*/
		/* 7: empty						*/

		char		sqlext[8];
	};

	extern DLLIMPORT struct sqlca sqlca;


#ifdef __cplusplus
}

#endif

#endif

#line 4 "Ruestung.pgcc"

#include <gtk--/main.h>


cH_Ruestung::cache_t cH_Ruestung::cache;

cH_Ruestung::cH_Ruestung(const std::string& name)
{
 cH_Ruestung *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
   *this=cH_Ruestung(new Ruestung(name));
   cache.Register(name,*this);
  }
}

Ruestung::Ruestung(const std::string& n) 
: name(n)
{
  /* exec sql begin declare section */
      
       
  
#line 25 "Ruestung.pgcc"
   char  db_name [ 50 ]   ,  db_long [ 50 ]   ,  db_region [ 50 ]   ;
 
#line 26 "Ruestung.pgcc"
   int  db_lp_verlust   ,  db_min_staerke   ,  db_rw_verlust   ,  db_b_verlust   ;
/* exec sql end declare section */
#line 27 "Ruestung.pgcc"

  strncpy(db_name,Name().c_str(),sizeof(db_name));
  

/* declare R1Iein  cursor for select  ruestung  , coalesce( region  , '' ) , lp_verlust  , min_staerke  , rw_verlust  , b_verlust   from ruestung where ruestung_s  = ?   */
#line 31 "Ruestung.pgcc"

  Transaction tr;
  { ECPGdo(__LINE__, NULL, "declare R1Iein  cursor for select  ruestung  , coalesce( region  , '' ) , lp_verlust  , min_staerke  , rw_verlust  , b_verlust   from ruestung where ruestung_s  = ?  ", 
	ECPGt_char,(db_name),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 33 "Ruestung.pgcc"

  SQLerror::test(__FILELINE__);
  
{ ECPGdo(__LINE__, NULL, "fetch R1Iein", ECPGt_EOIT, 
	ECPGt_char,(db_long),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_region),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(db_lp_verlust),1L,1L,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(db_min_staerke),1L,1L,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(db_rw_verlust),1L,1L,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(db_b_verlust),1L,1L,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 36 "Ruestung.pgcc"

  SQLerror::test(__FILELINE__);
  longname=db_long;
  region=db_region;
  lp_verlust=db_lp_verlust;
  min_staerke=db_min_staerke;
  rw_verlust=db_rw_verlust;
  b_verlust=db_b_verlust;
}

Ruestung_All::Ruestung_All(Gtk::ProgressBar *progressbar)
{
 /* exec sql begin declare section */
    
    
 
#line 49 "Ruestung.pgcc"
   char  db_name [ 100 ]   ;
 
#line 50 "Ruestung.pgcc"
   int  db_size   ;
/* exec sql end declare section */
#line 51 "Ruestung.pgcc"

 { ECPGdo(__LINE__, NULL, "select  count ( ruestung_s  )  from ruestung   ", ECPGt_EOIT, 
	ECPGt_int,&(db_size),1L,1L,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 52 "Ruestung.pgcc"

 /* declare RIein  cursor for select distinct ruestung_s   from ruestung    */
#line 53 "Ruestung.pgcc"

 Transaction tr;
 { ECPGdo(__LINE__, NULL, "declare RIein  cursor for select distinct ruestung_s   from ruestung   ", ECPGt_EOIT, ECPGt_EORT);}
#line 55 "Ruestung.pgcc"

 SQLerror::test(__FILELINE__);
 double count=0;
 while(true)
  {
   progressbar->set_percentage(count/db_size);
   while(Gtk::Main::events_pending()) Gtk::Main::iteration() ;
   { ECPGdo(__LINE__, NULL, "fetch RIein", ECPGt_EOIT, 
	ECPGt_char,(db_name),100L,1L,100*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 62 "Ruestung.pgcc"

   SQLerror::test(__FILELINE__,100);  
   if (sqlca.sqlcode) break;
   list_All.push_back(cH_Ruestung(db_name));
   ++count;
  }
 { ECPGdo(__LINE__, NULL, "close RIein", ECPGt_EOIT, ECPGt_EORT);}
#line 68 "Ruestung.pgcc"

 tr.close();
 progressbar->set_percentage(1);
}
