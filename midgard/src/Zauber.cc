/* Processed by ecpg (2.9.0) */
/* These three include files are added by the preprocessor */
#include <ecpgtype.h>
#include <ecpglib.h>
#include <ecpgerrno.h>
#line 1 "Zauber.pgcc"
#include "Zauber.hh"
#include "midgard_CG.hh"
#include <Aux/SQLerror.h>
#include <Aux/Transaction.h>
#include "class_typen.hh"

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

#line 6 "Zauber.pgcc"


cH_Zauber::cache_t cH_Zauber::cache;

cH_Zauber::cH_Zauber(const std::string& name,const vector<H_Data_typen>& Typ,int lernpunkte=0)
{
 st_index index(name,Typ,lernpunkte);
 cH_Zauber *cached(cache.lookup(index));
 if (cached) *this=*cached;
 else
  {
   *this=cH_Zauber(new Zauber(name,Typ,lernpunkte));
   cache.Register(index,*this);
  }
}

void Zauber::get_Zauber()
{
  /* exec sql begin declare section */
    
    
    
    
    
    
    
    
        
          
           
          
  
#line 25 "Zauber.pgcc"
   char  db_ursprung [ 50 ]   ;
 
#line 26 "Zauber.pgcc"
   int  db_kosten   ;
 
#line 27 "Zauber.pgcc"
   char  db_stufe [ 10 ]   ;
 
#line 28 "Zauber.pgcc"
   char  db_spruchrolle [ 10 ]   ;
 
#line 29 "Zauber.pgcc"
   char  query [ 1000 ]   ;
 
#line 30 "Zauber.pgcc"
   char  db_region [ 10 ]   ;
 
#line 31 "Zauber.pgcc"
   char  db_zauberart [ 30 ]   ;
 
#line 32 "Zauber.pgcc"
   char  db_p_element [ 30 ]   ,  db_s_element [ 30 ]   ;
 
#line 33 "Zauber.pgcc"
   char  db_ap [ 10 ]   ,  db_art [ 20 ]   ,  db_agens [ 30 ]   ,  db_prozess [ 30 ]   ,  db_reagens [ 30 ]   ,  db_zauberdauer [ 30 ]   ,  db_reichweite [ 10 ]   ,  db_wirkungsziel [ 30 ]   ,  db_wirkungsbereich [ 30 ]   ,  db_wirkungsdauer [ 20 ]   ,  db_material [ 50 ]   ,  db_thaumagram [ 10 ]   ,  db_effekt [ 1024 ]   ;
/* exec sql end declare section */
#line 37 "Zauber.pgcc"

  
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
   { ECPGprepare(__LINE__, "cl_zauber_ein_", query);}
#line 52 "Zauber.pgcc"

   /* declare cl_zauber_ein  cursor for ? */
#line 53 "Zauber.pgcc"


   { ECPGdo(__LINE__, NULL, "declare cl_zauber_ein  cursor for ?", 
	ECPGt_char_variable,(ECPGprepared_statement("cl_zauber_ein_")),1L,1L,1*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 56 "Zauber.pgcc"

   SQLerror::test(__FILELINE__);
   




{ ECPGdo(__LINE__, NULL, "fetch cl_zauber_ein", ECPGt_EOIT, 
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
#line 63 "Zauber.pgcc"

   SQLerror::test(__FILELINE__);

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
   { ECPGdo(__LINE__, NULL, "close cl_zauber_ein", ECPGt_EOIT, ECPGt_EORT);}
#line 88 "Zauber.pgcc"

   tr.close();
}

int Zauber::Kosten() const
{
  double fac; 
    if      (midgard_CG::standard_one_G(Standard()) ) fac = 0.5;
    else if (midgard_CG::standard_all_S(Standard()) ) fac = 1.0;
    else fac = 5.0; 

  return (int)(fac*GrundKosten());
}

int Zauber::Kosten_eBe(const std::string& pe,const std::string& se) const
{
  double fac; 
    if      (P_Element() == pe ) fac = 0.5;
    else if (S_Element() == se ) fac = 1.0;
    else fac = 5.0;  
  return (int)(fac*GrundKosten());
}

int Zauber::Erfolgswert(const vector<H_Data_typen>& Typ,const Grundwerte& Werte) const
{
   assert(Typ.size()==2);
   int ifac=-2;
   if (standard[0]=="G" || standard[1]=="G") ifac=0;

   int ispez=0;
   if (Typ[0]->Short()=="Ma" || Typ[1]->Short()=="Ma") 
      ispez = get_spezial_zauber_for_magier(Werte);

   int erf = Werte.Zaubern_wert()+Werte.bo_Za() + ifac + ispez ;
   return erf;
}

int Zauber::get_spezial_zauber_for_magier(const Grundwerte& Werte) const
{
 /* exec sql begin declare section */
    
       
     
    
 
#line 131 "Zauber.pgcc"
   char  db_ergebnis [ 20 ]   ;
 
#line 132 "Zauber.pgcc"
   char  db_agens [ 20 ]   ;
 
#line 133 "Zauber.pgcc"
   char  db_prozess [ 20 ]   ;
 
#line 134 "Zauber.pgcc"
   char  db_zauber [ 100 ]   ;
/* exec sql end declare section */
#line 135 "Zauber.pgcc"

 strncpy(db_zauber,Name().c_str(),sizeof(db_zauber));
 

{ ECPGdo(__LINE__, NULL, "select  ma  , agens  , prozess   from arkanum_zauber where name  = ?  ", 
	ECPGt_char,(db_zauber),100L,1L,100*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(db_ergebnis),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_agens),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_prozess),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 139 "Zauber.pgcc"

 SQLerror::test(__FILELINE__);

 int ispez=0;
 std::string ergebnis = db_ergebnis;
 std::string agens=db_agens;
 std::string prozess=db_prozess;

 if (ergebnis!="G" && agens==Werte.Spezial()) ispez = 2;
 if (ergebnis!="G" && prozess==Werte.Spezial()) ispez = 2;
 return ispez;
}

void Zauber::set_Standard(const vector<H_Data_typen>& Typ)
{
  /* exec sql begin declare section */
    
    
  
#line 155 "Zauber.pgcc"
   char  db_standard [ 20 ]   ,  db_standard2 [ 20 ]   ;
 
#line 156 "Zauber.pgcc"
   char  query [ 1000 ]   ;
/* exec sql end declare section */
#line 157 "Zauber.pgcc"

  strncpy(db_standard2,"",sizeof(db_standard2));
  std::string squery = "SELECT ";
  if (Typ[0]->is_mage()) squery += " coalesce("+Typ[0]->Short()+",'') "; 
  if (Typ[0]->is_mage() && (Typ[1]->Short()!="" && Typ[1]->is_mage())) squery += ",";
  if (Typ[1]->Short()!="" && Typ[1]->is_mage()) squery += " coalesce("+Typ[1]->Short()+",'') ";
  squery += " FROM arkanum_zauber WHERE name = '"+Name()+"'";
  strncpy(query,squery.c_str(),sizeof(query));
  Transaction tr;
  { ECPGprepare(__LINE__, "standard_zauber_ein_", query);}
#line 166 "Zauber.pgcc"

  /* declare standard_zauber_ein  cursor for ? */
#line 167 "Zauber.pgcc"

  { ECPGdo(__LINE__, NULL, "declare standard_zauber_ein  cursor for ?", 
	ECPGt_char_variable,(ECPGprepared_statement("standard_zauber_ein_")),1L,1L,1*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 168 "Zauber.pgcc"

  SQLerror::test(__FILELINE__);
  if (Typ[0]->is_mage() && Typ[1]->is_mage())     { ECPGdo(__LINE__, NULL, "fetch standard_zauber_ein", ECPGt_EOIT, 
	ECPGt_char,(db_standard),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(db_standard2),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 171 "Zauber.pgcc"

  else     { ECPGdo(__LINE__, NULL, "fetch standard_zauber_ein", ECPGt_EOIT, 
	ECPGt_char,(db_standard),20L,1L,20*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 173 "Zauber.pgcc"

  SQLerror::test(__FILELINE__);
  standard.clear();
  standard.push_back(db_standard);
  standard.push_back(db_standard2);
}
