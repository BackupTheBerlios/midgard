/* Processed by ecpg (2.8.0) */
/* These three include files are added by the preprocessor */
#include <ecpgtype.h>
#include <ecpglib.h>
#include <ecpgerrno.h>
#line 1 "Zauber.pgcc"
#include "Zauber.hh"
#include <Aux/SQLerror.h>
#include <Aux/Transaction.h>
#include "class_typen.hh"

#line 1 "/usr/local/pgsql/include/sqlca.h"
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

	extern struct sqlca sqlca;


#ifdef __cplusplus
}

#endif

#endif

#line 4 "Zauber.pgcc"


cH_Zauber::cache_t cH_Zauber::cache;

cH_Zauber::cH_Zauber(const std::string& name)
{
 cH_Zauber *cached(cache.lookup(name));
 if (cached) *this=*cached;
 else
  {
   *this=cH_Zauber(new Zauber(name));
   cache.Register(name,*this);
  }

}

void Zauber::get_Zauber()
{
  /* exec sql begin declare section */
    
    
    
    
    
    
    
    
        
          
           
          
  
#line 23 "Zauber.pgcc"
   char  db_ursprung [ 50 ]   ;
 
#line 24 "Zauber.pgcc"
   int  db_kosten   ;
 
#line 25 "Zauber.pgcc"
   char  db_stufe [ 10 ]   ;
 
#line 26 "Zauber.pgcc"
   char  db_spruchrolle [ 10 ]   ;
 
#line 27 "Zauber.pgcc"
   char  query [ 1000 ]   ;
 
#line 28 "Zauber.pgcc"
   char  db_region [ 10 ]   ;
 
#line 29 "Zauber.pgcc"
   char  db_zauberart [ 30 ]   ;
 
#line 30 "Zauber.pgcc"
   char  db_p_element [ 30 ]   ,  db_s_element [ 30 ]   ;
 
#line 31 "Zauber.pgcc"
   char  db_ap [ 10 ]   ,  db_art [ 20 ]   ,  db_agens [ 30 ]   ,  db_prozess [ 30 ]   ,  db_reagens [ 30 ]   ,  db_zauberdauer [ 30 ]   ,  db_reichweite [ 10 ]   ,  db_wirkungsziel [ 30 ]   ,  db_wirkungsbereich [ 30 ]   ,  db_wirkungsdauer [ 20 ]   ,  db_material [ 50 ]   ,  db_thaumagram [ 10 ]   ,  db_effekt [ 1024 ]   ;
/* exec sql end declare section */
#line 35 "Zauber.pgcc"

  
  std::string squery = "SELECT coalesce(z.ursprung,''), 
      z.kosten, z.stufe, coalesce(z.spruchrolle,''), coalesce(z.region,''), 
      coalesce(z.zauberart,''),coalesce(z.p_element,''), 
      coalesce(z.s_element,''), z.ap, z.art, coalesce(z.agens,''),
      coalesce(z.prozess,''), coalesce(z.reagens,''),z.zauberdauer,
      z.reichweite,z.wirkungsziel,z.wirkungsbereich,
      z.wirkungsdauer,coalesce(z.material),coalesce(z.thaumagram,''),coalesce(z.effekt,'')
      FROM arkanum_zauber z
      WHERE name = '"+name+"'";
   strncpy(query,squery.c_str(),sizeof(query));
   Transaction tr;
   { ECPGprepare(__LINE__, "zauber_ein_", query);}
#line 50 "Zauber.pgcc"

   /* declare zauber_ein  cursor for ? */
#line 51 "Zauber.pgcc"


   { ECPGdo(__LINE__, NULL, "declare zauber_ein  cursor for ?", 
	ECPGt_char_variable,(ECPGprepared_statement("zauber_ein_")),1L,1L,1*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 53 "Zauber.pgcc"

   SQLerror::test(__FILELINE__);
   




{ ECPGdo(__LINE__, NULL, "fetch zauber_ein", ECPGt_EOIT, 
	ECPGt_char,(db_ursprung),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(db_kosten),1L,1L,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_stufe),10L,1L,10*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_spruchrolle),10L,1L,10*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_region),10L,1L,10*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_zauberart),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_p_element),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_s_element),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_ap),10L,1L,10*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_art),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_agens),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_prozess),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_reagens),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_zauberdauer),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_reichweite),10L,1L,10*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_wirkungsziel),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_wirkungsbereich),30L,1L,30*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_wirkungsdauer),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_material),50L,1L,50*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_thaumagram),10L,1L,10*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_effekt),1024L,1L,1024*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 60 "Zauber.pgcc"


   ursprung=db_ursprung;   
   kosten=db_kosten;
   stufe=db_stufe;
   spruchrolle=db_spruchrolle;
   region=db_region;
   zauberart=db_zauberart;
   p_element=db_p_element;
   s_element=db_s_element;
   ap=db_ap;
   art=db_art;
   stufe=db_stufe;
   zauberdauer=db_zauberdauer;
   reichweite=db_reichweite;
   wirkungsziel=db_wirkungsziel;
   wirkungsbereich=db_wirkungsbereich;
   wirkungsdauer=db_wirkungsdauer;
   ursprung=db_ursprung;
   material=db_material;
   agens=db_agens;
   prozess=db_prozess;
   reagens=db_reagens;
   beschreibung=db_effekt;
}

double Zauber::get_Faktor(const vector<Data_typen>& Typen,const Grundwerte& Werte) const
{
  double fac;
  if (Typen[0].Short() != "eBe" || (P_Element()=="" && S_Element()==""))
   {
    if      (Standard()=="G" || Standard2()=="G") fac = 0.5;
    else if (Standard()=="S" && ( Standard2()=="S" || Standard2()=="" )) fac = 1.0;
    else if (Standard2()=="S" && ( Standard()=="S" || Standard()=="" )) fac = 1.0; 
    else fac = 5.0; 
   }
  else
   {
    if (P_Element()==Werte.Spezial())  fac = 0.5;
    if (S_Element()==Werte.Spezial2()) fac = 1;  
    else fac = 0;
   }
  return(fac);
}
