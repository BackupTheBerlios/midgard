#include "midgard_CG.hh"

void midgard_CG::latex_beschreibung_drucken()
{   
 ofstream fout("tmp_b.tex");
 fout << werte.beschreibung<<"\n";
 fout.close();
 system("latex "PACKAGE_DATA_DIR"charakter_beschreibung.tex");
 system("dvips charakter_beschreibung.dvi");
 system("gv charakter_beschreibung.ps &");

}
