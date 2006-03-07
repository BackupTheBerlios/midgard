<?php

//
// MAGuS Charaktereingabe: XML-Ausgabe V0.4.2 060228 (c) by sandro@filippetti.de
//

$AFERT=$_GET['AFERT'];
$FERTIG=$_GET['FERTIG'];
$WAFFE=$_GET['WAFFE'];
$WAFFEGK=$_GET['WAFFEGK'];
$SPRACHE=$_GET['SPRACHE'];
$SCHRIFT=$_GET['SCHRIFT'];
$ZAUBER=$_GET['ZAUBER'];

//header("Content-Type: application/magus");
header("Content-Type: application/xml-external-parsed-entity");
header('Content-Disposition: attachment; filename="MAGuS-Charakter.magus"');


echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
echo "<MAGUS-data>\n";
echo " <Midgard-Abenteurer Version=\"10\">\n";
echo "  <Figur ",
          "Grad=\"",$_GET[GRAD],"\" ",
          "Name=\"",$_GET[CharNAME],"\" ";
          if ($_GET[SPIELER]) echo "Spieler=\"",$_GET[SPIELER],"\" ";
          echo "Zeitpunkt=\"Online Eingabe\"/>\n";
echo "  <Typ ",
          "Abkürzung=\"",$_GET[TYP],"\" ";
          if ($_GET[TYP2]) echo "Abkürzung2=\"",$_GET[TYP2],"\" ";
          echo 
            "Geschlecht=\"",$_GET[SEX],"\" ",
            "Hand=\"",$_GET[HAND],"\" ",
            "Muttersprache=\"",$_GET[MSPRACHE],"\" ";
          if ($_GET[SPEZG]) {
            echo "Spezialgebiet=\"",$_GET[SPEZG],"\" ";
            if ($_GET[SPEZIALISIERUNG]) {echo "Spezialisierung=\"",$_GET[SPEZIALISIERUNG],"\" ";}
            else {echo "Spezialisierung=\"",$_GET[SPEZG],"\" ";}
          }
          echo
            "Spezies=\"",$_GET[SPEZIES],"\" ",
            "Stadt_Land=\"",$_GET[HERKSL],"\" ",
            "Überleben=\"",$_GET[UEH],"\"/>\n";
echo "  <Basiseigenschaften ",
          "Gs=\"",$_GET[GS],"\" ",
          "Gw=\"",$_GET[GW],"\" ",
          "In=\"",$_GET[IN],"\" ",
          "Ko=\"",$_GET[KO],"\" ",
          "St=\"",$_GET[ST],"\" ",
          "Zt=\"",$_GET[ZT],"\" />\n";
echo "  <abgeleiteteEigenschaften ",        
          "Au=\"",$_GET[AU],"\" ",
          "B=\"",$_GET[BEW],"\" ";
          if ($_GET[SG]) echo "SG=\"",$_GET[SG],"\" ";
          if ($_GET[GG]) echo "GG=\"",$_GET[GG],"\" ";
          echo "Sb=\"",$_GET[SB],"\" ",
          "Wk=\"",$_GET[WK],"\" ",
          "pA=\"",$_GET[PA],"\" />\n";
          
echo "  <Erfolgswerte ",
          "Abwehr=\"",$_GET[ABWH],"\" ",
          "ZauberResistenz=\"",$_GET[ZRES],"\" ",
          "Zaubern=\"",$_GET[EWZAU],"\" />\n";
echo "  <Gesundheit ",
          "AP=\"",$_GET[AP],"\" ",
          "LP=\"",$_GET[LP],"\" />\n";
echo "  <Beschreibung ",
          "Alter=\"",$_GET[AGE],"\" ",
          "Gestalt=\"",$_GET[GESTALT],"\" ",
          "Gewicht=\"",$_GET[WEIGHT],"\" ";
          if ($_GET[RELIG]) echo "Glaube=\"",$_GET[RELIG],"\" ";
          echo "Größe=\"",$_GET[SIZE],"\" ",
          "Herkunft=\"",$_GET[HERK],"\" ",
          "Stand=\"",$_GET[STAND],"\" />\n";
echo "  <Vermögen/>\n";
echo "  <Steigern ",
          "EPproGFP=\"0\" GFP=\"",$_GET[GFP],"\">\n";
echo "    <Praxispunkte ";
          if ($_GET[PPABWH]) echo "Abwehr=\"",$_GET[PPABWH],"\" ";
          if ($_GET[PPZRES]) echo "Resistenz=\"",$_GET[PPZRES],"\" ";
          if ($_GET[PPEWZAU]) echo "Zaubern=\"",$_GET[PPEWZAU],"\" ";
echo      "/>\n";
echo "  </Steigern>\n";
echo "  <Text Größe=\"8\"/>\n";
echo "  <Ausrüstung>\n";
echo "   <Rüstung>OR</Rüstung>\n";
echo "   <Rüstung2>OR</Rüstung2>\n";
echo "   <Gegenstand Bezeichnung=\"Körper\" sichtbar=\"true\">\n";
echo "    <Gegenstand Bezeichnung=\"Hose\" sichtbar=\"true\"/>\n";
echo "    <Gegenstand Bezeichnung=\"Hemd\" sichtbar=\"true\"/>\n";
echo "    <Gegenstand Bezeichnung=\"Gürtel\" sichtbar=\"true\"/>\n";
echo "    <Gegenstand Bezeichnung=\"Schuhe\" sichtbar=\"true\"/>\n";
echo "    <Gegenstand Besonderheit=\"Leder\" Bezeichnung=\"Rucksack\" sichtbar=\"true\">\n";
echo "     <Gegenstand Besonderheit=\"warm\" Bezeichnung=\"Decke\" sichtbar=\"true\"/>\n";
echo "     <Gegenstand Bezeichnung=\"Lederbeutel\" sichtbar=\"true\"/>\n";
echo "     <Gegenstand Bezeichnung=\"Geld\"/>\n";
echo "    </Gegenstand>\n";
echo "   </Gegenstand>\n";
echo "  </Ausrüstung>\n";
echo "  <Fertigkeiten>\n";
echo "   <Sinn Bezeichnung=\"Sehen\" Wert=\"",$_GET[AUGE],"\"/>\n";
echo "   <Sinn Bezeichnung=\"Hören\" Wert=\"",$_GET[OHR],"\"/>\n";
echo "   <Sinn Bezeichnung=\"Riechen\" Wert=\"",$_GET[NASE],"\"/>\n";
echo "   <Sinn Bezeichnung=\"Schmecken\" Wert=\"",$_GET[ZUNGE],"\"/>\n";
echo "   <Sinn Bezeichnung=\"Tasten\" Wert=\"",$_GET[TASTEN],"\"/>\n";
echo "   <Sinn Bezeichnung=\"Sechster Sinn\" Wert=\"",$_GET[SIXTHS],"\"/>\n";
echo "   <Beruf Bezeichnung=\"",$_GET[BERUF],"\"/>\n";
         $i=0;         
         if ($AFERT[NAME][$i]) {         
         while (($AFERT[NAME][$i]) AND ($i<10)){
          echo 
           "   <ang-Fertigkeit Bezeichnung=\"",$AFERT[NAME][$i],"\" ",
           "Wert=\"",$AFERT[WERT][$i],"\"",
           "/>\n";
          $i++;
         }
         }
         $i=0;         
         if ($FERTIG[NAME][$i]) {         
         while (($FERTIG[NAME][$i])){
          echo 
           "   <Fertigkeit ",
           "Bezeichnung=\"",$FERTIG[NAME][$i],"\" ";
           if ($FERTIG[PP][$i]) echo "Praxispunkte=\"",$FERTIG[PP][$i],"\" ";
           echo "Wert=\"",$FERTIG[WERT][$i],"\"";           
           if ($FERTIG[ZUSATZ][$i]) echo " Zusatz=\"",$FERTIG[ZUSATZ][$i],"\"";
           echo "/>\n";
          $i++;
         }
         }
         $i=0;         
         if ($WAFFE[NAME][$i]) {         
         while (($WAFFE[NAME][$i])){
          echo 
           "   <Waffe ",
           "Bezeichnung=\"",$WAFFE[NAME][$i],"\" ";
           if ($WAFFE[PP][$i]) echo "Praxispunkte=\"",$WAFFE[PP][$i],"\" ";
           echo "Wert=\"",$WAFFE[WERT][$i],"\"",
           "/>\n";
          $i++;
         }
         }
         $i=0;         
         if ($ZAUBER[NAME][$i]) {         
         while (($ZAUBER[NAME][$i])){
          echo 
           "   <Zauber ",
           "Bezeichnung=\"",$ZAUBER[NAME][$i],"\"";           
           if ($ZAUBER[ZUSATZ][$i]) echo " Zusatz=\"",$ZAUBER[ZUSATZ][$i],"\"";
           echo
           "/>\n";
          $i++;
         }
         }
         $i=0;         
//         if ($_GET[WAFFEGK][$i]) {         
         while (($_GET[WAFFEGK][$i])){
          echo 
           "   <Grundkenntnis ",
           "Bezeichnung=\"",$_GET[WAFFEGK][$i],"\"",
           "/>\n";
          $i++;
         }
//         }
         $i=0;   
         echo "   <Sprache Bezeichnung=\"",$_GET[MSPRACHE],"\" Wert=\"",$_GET[WMSPRACHE],"\" />\n";
         if ($SPRACHE[NAME][$i]) {         
         while (($SPRACHE[NAME][$i])){
          echo 
           "   <Sprache ",
           "Bezeichnung=\"",$SPRACHE[NAME][$i],"\" ";
           if ($SPRACHE[PP][$i]) echo "Praxispunkte=\"",$SPRACHE[PP][$i],"\" ";
           echo "Wert=\"",$SPRACHE[WERT][$i],"\"",
           "/>\n";
          $i++;
         }
         }
         $i=0;         
         if ($SCHRIFT[NAME][$i]) {         
         while (($SCHRIFT[NAME][$i])){
          echo 
           "   <Urschrift ",
           "Bezeichnung=\"",$SCHRIFT[NAME][$i],"\" ",
           "Buchstaben=\"",$SCHRIFT[ALPHABET][$i],"\" ";
           if ($SCHRIFT[PP][$i]) echo "Praxispunkte=\"",$SCHRIFT[PP][$i],"\" ";
           echo "Wert=\"",$SCHRIFT[WERT][$i],"\"",
           "/>\n";
          $i++;
         }
         }
         

echo "  </Fertigkeiten>\n";
echo "  <Optionen>\n";
echo "   <CheckOptions Name=\"Originalregeln\" Wert=\"false\"/>\n";
echo "   <CheckOptions Name=\"NSC zulassen\" Wert=\"false\"/>\n";
echo "   <CheckOptions Name=\"Zauberbeschreibung ausdrucken\" Wert=\"false\"/>\n";
echo "   <CheckOptions Name=\"1 GS entspricht 1 GFP\" Wert=\"false\"/>\n";
echo "   <CheckOptions Name=\"Grundwerte über 100 zulassen\" Wert=\"false\"/>\n";
echo "  </Optionen>\n";
echo " </Midgard-Abenteurer>\n";
echo "</MAGUS-data>\n";
?>