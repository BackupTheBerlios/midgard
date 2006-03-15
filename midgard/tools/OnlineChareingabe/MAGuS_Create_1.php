<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
  <title>MAGuS - Online Abenteurereingabe</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <style type="text/css">
   .must
   { background-color:#FFD4D1; }
   .may
   { background-color:#C6FFEA; }
   .att
   {color:#FF0105; }
   .chif
   {text-align:right;}
  </style>
</head>
<body>
<?php
//
// MAGuS Charaktereingabe: Datenabfrage V0.4.3 060302 (c) by sandro@filippetti.de
//
$AnzFert = $_GET[AnzFert];
$AnzAFert = $_GET[AnzAFert];
$AnzWaf = $_GET[AnzWaf];
$AnzEWaf = $_GET[AnzEWaf];
$AnzWafGK = $_GET[AnzWafGK];
$AnzSpra = $_GET[AnzSpra];
$AnzSchri = $_GET[AnzSchri];
$AnzEZaub = $_GET[AnzEZaub];
$AnzZaubZ = $_GET[AnzZaubZ];
$DCHAR = $_GET[DCHAR];
$AnzFertZ = $_GET[AnzFertZ];
$AnzEFert = $_GET[AnzEFert];
?>

<FORM action="./MAGuS_Create_Ausgabe.php" method="GET" enctype="application/x-www-form-urlencoded" accept-charset="utf-8">
<h2>MAGuS - Online Abenteurereingabe</h2>
<br>
In dieses Formular bitte die Daten der Figur eingeben. <br>
Die eingegebenen Daten werden nicht auf Plausibilit&auml;t gepr&uuml;ft!<br>
<br>
<span class="must">&nbsp;&nbsp;</span>&nbsp;hinterlegte Felder <i>m&uuml;ssen</i> ausgef&uuml;llt werden<br>
<span class="may">&nbsp;&nbsp;</span>&nbsp;hinterlegte Felder k&ouml;nnen <i>optional</i> ausgef&uuml;llt werden.<br>
Werte in wei&szlig;en Feldern k&ouml;nnen ge&auml;ndert werden (unver&auml;nderte Werte werden &uuml;bernommen)<br>

<br>
<table>
  <tr bgcolor="#ccebff">
    <td valign="top">Grunddaten</td>
    <td>
      <table>
      <tr>
        <td>Name:</td><td><INPUT type="text" class="must" name="CharNAME" size="30" maxlength="30"></td>  
        <td>Spieler</td><td><INPUT type="text" class="may" name="SPIELER" size="20" maxlength="30"></td>  
      </tr>
      <tr>
       <td>Grad</td><td><INPUT type="text" class="must" name="GRAD" size="2" maxlength="2"></td>       
       <td>Beruf</td><td><INPUT type="text" class="may" name="BERUF" size="20" maxlength="20"></td> 
      </tr>
      <tr>
        <td></td><td></td>
        <td>Glaube</td><td><INPUT type="text" class="may" name="RELIG" size="20" maxlenght="20"></td>
      </tr>
      </table>
       <br>
      <table>
      <tr>
        <td>Spezies</td>
        <td>
         <select name="SPEZIES" size="1">
           <option>Mensch</option>
           <option>Berggnom</option>
           <option>Elf</option>
           <option>Halbling</option>
           <option>Waldgnom</option>
           <option>Zwerg</option>
         </select>
        </td>  
        <td>Typ</td>
        <td>
         <select name="TYP" size="1">
           <option value="As">Assassine</option>
           <option value="BN">Nordlandbarbar</option>
           <option value="BS">Steppenbarbar</option>
           <option value="BW">Waldlandbarbar</option>
           <option value="Ba">Barde</option>
           <option value="De">Derwisch</option>
           <option value="Dr">Druide</option>
           <option value="Dt">Deuter</option>
           <option value="Er">Ermittler</option>
           <option value="Fi">Fian</option>
           <option value="Gl">Gl&uuml;cksritter</option>
           <option value="Hj">Hexenj&auml;ger</option>
           <option value="Hl">Heiler</option>
           <option value="Hä">H&auml;ndler</option>
           <option value="Kd">Kidoka</option>
           <option value="Km">Klingenmagier</option>
           <option value="Kr">Krieger</option>
           <option value="Ku">Kundschafter</option>
           <option value="MMa">Meeresmagier</option>
           <option value="Ma">Magier</option>
           <option value="Mg">Magister</option>
           <option value="Ny">Ninya</option>
           <option value="Or">Ordenskrieger</option>
           <option value="PC">Chaospriester</option>
           <option value="PF">Fruchtbarkeitspriester</option>
           <option value="PHa">Priester Handel/Handwerk</option>
           <option value="PHe">Herrschaftspriester</option>
           <option value="PK">Kriegspriester</option>
           <option value="PM">Meerespriester</option>
           <option value="PT">Todespriester</option>
           <option value="PW">Weisheitspriester</option>
           <option value="RiN">Ritter [Alba, K&uuml;stenstaaten]</option>
           <option value="RiS">Ritter [Aran,Eschar]</option>
           <option value="Ru">Runenschneider</option>
           <option value="Sa">Saddhu</option>
           <option value="ScN">Nordlandschamane</option>
           <option value="ScS">Steppenschamane</option>
           <option value="ScW">Waldlandschamane</option>           
           <option value="Se">Seefahrer</option>
           <option value="Sk">Skalde</option>
           <option value="Sp">Spitzbube</option>
           <option value="Sr">Srikumara</option>
           <option value="Sw">Schattenweber</option>
           <option value="Sö">S&ouml;ldner</option>
           <option value="Th">Thaumaturg</option>
           <option value="Tm">Tiermeister</option>
           <option value="To">Todeswirker</option>
           <option value="Tr">Trickser</option>
           <option value="Tt">Tempelt&auml;nzer</option>
           <option value="Wa">Waldl&auml;ufer</option>
           <option value="Wi">Wildl&auml;ufer</option>
           <option value="dBe">D&auml;monenbeschw&ouml;rer</option>
           <option value="eBe">Elementarbeschw&ouml;rer</option>
           <option value="gHx">grauer Hexer</option>
           <option value="sHx">schwarzer Hexer</option>
           <option value="tBe">Totenbeschw&ouml;rer</option>
           <option value="wHx">wei&szlig;er Hexer</option>           
         </select>
        </td>  
      </tr>
      <tr>
      <?php
        if ($DCHAR=="YES") {
         echo "<td class=\"att\">Doppelcharakter</td><td></td>";
        }
        else {
         echo "<td></td><td></td>";
        }        
        if ($DCHAR=="YES") {
          echo 
          "<td class=\"att\">Typ 2</td>",
          "<td>",
          "<select name=\"TYP2\" size=\"1\">",
           "<option value=\"As\">Assassine</option>",
           "<option value=\"BN\">Nordlandbarbar</option>",
           "<option value=\"BS\">Steppenbarbar</option>",
           "<option value=\"BW\">Waldlandbarbar</option>",
           "<option value=\"Ba\">Barde</option>",
           "<option value=\"De\">Derwisch</option>",
           "<option value=\"Dr\">Druide</option>",
           "<option value=\"Dt\">Deuter</option>",
           "<option value=\"Er\">Ermittler</option>",
           "<option value=\"Fi\">Fian</option>",
           "<option value=\"Gl\">Gl&uuml;cksritter</option>",
           "<option value=\"Hj\">Hexenj&auml;ger</option>",
           "<option value=\"Hl\">Heiler</option>",
           "<option value=\"Hä\">H&auml;ndler</option>",
           "<option value=\"Kd\">Kidoka</option>",
           "<option value=\"Km\">Klingenmagier</option>",
           "<option value=\"Kr\">Krieger</option>",
           "<option value=\"Ku\">Kundschafter</option>",
           "<option value=\"MMa\">Meeresmagier</option>",
           "<option value=\"Ma\">Magier</option>",
           "<option value=\"Mg\">Magister</option>",
           "<option value=\"Ny\">Ninya</option>",
           "<option value=\"Or\">Ordenskrieger</option>",
           "<option value=\"PC\">Chaospriester</option>",
           "<option value=\"PF\">Fruchtbarkeitspriester</option>",
           "<option value=\"PHa\">Priester Handel/Handwerk</option>",
           "<option value=\"PHe\">Herrschaftspriester</option>",
           "<option value=\"PK\">Kriegspriester</option>",
           "<option value=\"PM\">Meerespriester</option>",
           "<option value=\"PT\">Todespriester</option>",
           "<option value=\"PW\">Weisheitspriester</option>",
           "<option value=\"RiN\">Ritter [Alba, K&uuml;stenstaaten]</option>",
           "<option value=\"RiS\">Ritter [Aran,Eschar]</option>",
           "<option value=\"Ru\">Runenschneider</option>",
           "<option value=\"Sa\">Saddhu</option>",
           "<option value=\"ScN\">Nordlandschamane</option>",
           "<option value=\"ScS\">Steppenschamane</option>",
           "<option value=\"ScW\">Waldlandschamane</option>",           
           "<option value=\"Se\">Seefahrer</option>",
           "<option value=\"Sk\">Skalde</option>",
           "<option value=\"Sp\">Spitzbube</option>",
           "<option value=\"Sr\">Srikumara</option>",
           "<option value=\"Sw\">Schattenweber</option>",
           "<option value=\"Sö\">S&ouml;ldner</option>",
           "<option value=\"Th\">Thaumaturg</option>",
           "<option value=\"Tm\">Tiermeister</option>",
           "<option value=\"To\">Todeswirker</option>",
           "<option value=\"Tr\">Trickser</option>",
           "<option value=\"Tt\">Tempelt&auml;nzer</option>",
           "<option value=\"Wa\">Waldl&auml;ufer</option>",
           "<option value=\"Wi\">Wildl&auml;ufer</option>",
           "<option value=\"dBe\">D&auml;monenbeschw&ouml;rer</option>",
           "<option value=\"eBe\">Elementarbeschw&ouml;rer</option>",
           "<option value=\"gHx\">grauer Hexer</option>",
           "<option value=\"sHx\">schwarzer Hexer</option>",
           "<option value=\"tBe\">Totenbeschw&ouml;rer</option>",
           "<option value=\"wHx\">wei&szlig;er Hexer</option>",        
         "</select>",
        "</td>";
        }
        else {
        echo "<td></td><td></td>";
        }
      ?>  
      </tr>      
      <tr>
        <td>Geschlecht</td>
        <td>
          <select name="SEX" size="1">
           <option value="m">m&auml;nnlich</option>
           <option value="w">weiblich</option>
          </select>
        </td>
        <td>H&auml;ndigkeit</td>
        <td>
          <select name="HAND" size="1">
           <option>Rechtsh&#228;nder</option>
           <option>Linksh&#228;nder</option>
           <option>Beidh&#228;ndig</option>
          </select>
        </td>  
       </tr>
       <tr>
        <td>Stadt/Land</td>
        <td>
          <select name="HERKSL" size="1">
           <option>Stadt</option>
           <option>Land</option>
          </select>
        </td>
        <td>Stand</td>
       <td>
          <select name="STAND" size="1">
           <option>Unfrei</option>
           <option>Volk</option>
           <option>Mittelschicht</option>
           <option>Adel</option>
          </select>
       </td>
      </tr>
      </table>
      <br>
      <table>
      <tr>
        <td>St</td><td><INPUT type="text" class="must"  name="ST" size="3" maxlength="3"></td> 
        <td>Gs</td><td><INPUT type="text" class="must"  name="GS" size="3" maxlength="3"></td> 
        <td>Gw</td><td><INPUT type="text" class="must"  name="GW" size="3" maxlength="3"></td> 
        <td>In</td><td><INPUT type="text" class="must"  name="IN" size="3" maxlength="3"></td> 
        <td>Ko</td><td><INPUT type="text" class="must"  name="KO" size="3" maxlength="3"></td>         
        <td>Zt</td><td><INPUT type="text" class="must"  name="ZT" size="3" maxlength="3"></td>
      </tr>
      <tr>
        <td>Au</td><td><INPUT type="text" class="must"  name="AU" size="3" maxlength="3"></td> 
        <td>pA</td><td><INPUT type="text" class="must"  name="PA" size="3" maxlength="3"></td> 
        <td>Sb</td><td><INPUT type="text" class="must"  name="SB" size="3" maxlength="3"></td> 
        <td>B </td><td><INPUT type="text" name="BEW" size="3" maxlength="3" value="24"></td> 
        <td>Wk</td><td><INPUT type="text" class="must"  name="WK" size="3" maxlength="3"></td> 
        <td></td><td></td>
      </tr>
      <tr>
        <td>AP</td><td><INPUT type="text" class="must"  name="AP" size="3" maxlength="3"></td> 
        <td>LP</td><td><INPUT type="text" class="must"  name="LP" size="3" maxlength="3"></td> 
        <td>GG</td><td><INPUT type="text" class="may"  name="GG" size="3" maxlength="2"></td> 
        <td>SG</td><td><INPUT type="text" class="may"  name="SG" size="3" maxlength="2"></td> 
        <td></td>
        <td></td><td></td>
      </tr>
      </table>
      <table>
      <tr>
       <td></td><td align="right">PP</td><td></td><td align="right">PP</td><td></td><td align="right">PP</td><td></td><td></td>
      </tr>
      <tr>
       <td>Abwehr</td><td><INPUT type="text" class="must" name="ABWH" size="2" maxlength="2">&nbsp;<INPUT type="text" class="may" name="PPABWH" size="2" maxlength="2"></td> 
       <td>Resistenz</td><td><INPUT type="text" class="must" name="ZRES" size="2" maxlength="2">&nbsp;<INPUT type="text" class="may" name="PPZRES" size="2" maxlength="2"></td> 
       <td>Zaubern</td><td><INPUT type="text" class="must" name="EWZAU" size="2" maxlength="2">&nbsp;<INPUT type="text" class="may" name="PPEWZAU" size="2" maxlength="2"></td> 
       <td>Alter</td><td><INPUT type="text" class="must" name="AGE" size="3" maxlength="4"></td>
       
      </tr>
      <tr>
         <td>Gewicht</td><td><INPUT type="text" class="must" name="WEIGHT" size="3" maxlength="3"> [kg]</td>
         <td>Gr&ouml;&szlig;e</td><td><INPUT type="text" class="must" name="SIZE" size="3" maxlength="3"> [cm]</td>
         <td>Gestalt</td>
         <td>
          <select name="GESTALT" size="1">
           <option>breit</option>
           <option>normal</option>
           <option>schlank</option>           
          </select>
       </td>
       <td>GFP</td><td><INPUT type="text" name="GFP" size="8" value="0" maxlength="6"></td>
      </tr>
      </table>
      <table>
      <tr>
        <td>Herkunft</td>
        <td>
          <select name="HERK" size="1">
           <option>Alba</option>
           <option>Aran</option>
           <option>Buluga</option>
           <option>Chryseia</option>
           <option>Clanngadarn</option>
           <option>Dvarheim</option>
           <option>Erainn</option>
           <option>Eschar</option>
           <option>Feuerinseln</option>
           <option>Fuardain</option>
           <option>Halfdal</option>
           <option>Ikengabecken</option>
           <option>Inseln unter dem Westwind</option>
           <option>KanThaiPan</option>
           <option>K&uuml;stenstaaten</option>
           <option>Medjis</option>
           <option>Minangpahit</option>
           <option>Moravod</option>
           <option>Nahuatlan</option>
           <option>Rawindra</option>
           <option>Tegarische Steppe</option>
           <option>Urruti</option>
           <option>Valian</option>
           <option>Waeland</option>
           <option>Ywerddon</option>
          </select>
       </td>
       <td>&Uuml;berleben (universell)</td>
       <td>
         <select name="UEH" size="1">
          <option>&#220;berleben Heimat</option>
          <option>&#220;berleben im Dschungel</option>
          <option>&#220;berleben im Gebirge</option>
          <option>&#220;berleben im Schnee</option>
          <option>&#220;berleben im Sumpf</option>
          <option>&#220;berleben im Wald</option>
          <option>&#220;berleben in der Steppe</option>
          <option>&#220;berleben in der W&#252;ste</option>
         </select>
       </td>         
      </tr>
      </table>
    </td>
  </tr>
  <tr bgcolor="#ffe3ff">
    <td>Sinne</td>
    <td>
      <table>
        <tr>
          <td>Sehen</td><td>+<INPUT type="text" name="AUGE" size="2" maxlength="2" value="8"></td> 
          <td>H&ouml;ren</td><td>+<INPUT type="text" name="OHR" size="2" maxlength="2" value="8"></td> 
          <td>Riechen</td><td>+<INPUT type="text" name="NASE" size="2" maxlength="2" value="8"></td> 
          <td>Schmecken</td><td>+<INPUT type="text" name="ZUNGE" size="2" maxlength="2" value="8"></td> 
          <td>Tasten</td><td>+<INPUT type="text" name="TASTEN" size="2" maxlength="2" value="8"></td> 
          <td>6.Sinn</td><td>+<INPUT type="text" name="SIXTHS" size="2" maxlength="2" value="3"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td valign="top" bgcolor="#FFF1D7">Fertigkeiten</td>
    <td>    
    <?php 
        if ($AnzAFert > 0) {
         echo "\n<table width=\"100%\" bgcolor=\"#ffe3ff\">";
         echo "<tr><td></td><td>Angeb.&nbsp;Fertigkeiten</td><td></td><td>Wert</td><td></td><td width=\"100%\"></td></tr>\n";
          for ($i=0; $i<$AnzAFert; $i++){
           echo "\n<tr>\n",
                "<td align=\"right\">",$i+1,")</td>\n",
                "<td>\n",
                 "<select name=\"AFERT[NAME][",$i,"]\" size=\"1\">\n",
                  "<option>Berserkergang</option>\n",
                  "<option>Einpr&auml;gen</option>\n",
                  "<option>Gute Reflexe</option>\n",
                  "<option>Nachtsicht</option>\n",
                  "<option>Richtungssinn</option>\n",
                  "<option>Robustheit</option>\n",
                  "<option>Wachgabe</option>\n",                  
                 "</select>\n", 
                "</td>\n", 
                "<td>+</td>\n",
                "<td><INPUT type=\"text\" class=\"must\" name=\"AFERT[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>\n",
                "<td></td>\n",
                "<td></td>\n",
               "</tr>\n\n";
          }
          echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>\n";
          echo "</table>\n";
         
        }        
        echo "\n<table bgcolor=\"#FFFBD2\" width=\"100%\">\n";
        echo "<tr><td>erlernte Fertigkeiten</td></tr>\n";             
        echo "</table>";
        echo "\n\n<table width=\"100%\" bgcolor=\"#FFFBD2\">\n";       
        echo "<tr><td></td><td>Fertigkeit</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\"></td></tr>\n";
        $i=0;
        while ($_GET["SELFERT"][$i]){
         echo 
           "<tr>\n",
           "<td align=\"right\">",$i+1,".</td>\n",
           "<td><INPUT type=\"text\" class=\"must\" name=\"FERTIG[NAME][",$i,"]\" value=\"",htmlentities(utf8_decode($_GET["SELFERT"][$i])),"\" readonly></td>\n",
           "<td align=\"right\">+</td>\n",
           "<td><INPUT type=\"text\" class=\"must\" name=\"FERTIG[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>\n",
           "<td><INPUT type=\"text\" class=\"may\" name=\"FERTIG[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>\n",
           "</tr>\n";
         $i++;
        }
        if ($_GET[SELFERTZ][0]){        
//        if ($AnzFertZ > 0){
        echo "<tr><td></td><td>Fertigkeit</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\">Zusatz</td></tr>\n";
       
        for ($h=0; $h<$AnzFertZ; $h++){
          
          echo 
            "<tr>\n",
            "<td align=\"right\">",$i+1,".</td>\n",
            "<td><select name=\"FERTIG[NAME][",$i,"]\" size=\"1\"\>\n";
            $j=0;
            while ($_GET["SELFERTZ"][$j]){
              echo "<option>",htmlentities(utf8_decode($_GET["SELFERTZ"][$j])),"</option>\n";
              $j++;
            }           
          echo
            "</select>\n",
            "<td align=\"right\">+</td>",
            "<td><INPUT type=\"text\" class=\"must\" name=\"FERTIG[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
            "<td><INPUT type=\"text\" class=\"may\" name=\"FERTIG[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
            "<td><INPUT type=\"text\" class=\"must\" name=\"FERTIG[ZUSATZ][",$i,"]\" size=\"30\" maxlength=\"50\"></td>",
            "</tr>\n";
          $i++;
        }
        }
        if ($AnzEFert > 0){
          echo "<tr><td></td><td>Fertigkeit</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\">Zusatz</td></tr>";
          for ($j=0; $j<$AnzEFert; $j++){
            
            echo "<tr>",
              "<td align=\"right\">",$i+1,".</td>",
              "<td><INPUT type=\"text\" class=\"must\" name=\"FERTIG[NAME][",$i,"]\" size=\"30\" maxlength=\"50\"></td>",
              "<td align=\"right\">+</td>",
              "<td><INPUT type=\"text\" class=\"must\" name=\"FERTIG[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
              "<td><INPUT type=\"text\" class=\"may\" name=\"FERTIG[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
              "<td><INPUT type=\"text\" class=\"may\" name=\"FERTIG[ZUSATZ][",$i,"]\" size=\"30\" maxlength=\"50\"></td>",
            "</tr>\n";  
            $i++;  
          }
        }
          echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>";
        echo "</table>";        
//        echo "\n<table bgcolor=\"#FFFBD2\" width=\"100%\">\n";
//        echo "<tr><td>",
//               "<font size=\"-1\">Unter &quot;Zusatz&quot; k&ouml;nnen zus&auml;tzliche Angaben bei einigen Fertigkeiten eingegeben werden<br>",
//               "(z.B: Musizieren -> <i>Instrument</i>) </font></td></tr>";
//        echo "<tr><td class=\"att\"><font size=\"-2\"><i>Bei der Eingabe der Fertigkeiten bitte auf die korrekte Schreibweise achten!</i></font></td></tr>";
//        echo "</table>";
        echo "\n<table bgcolor=\"#FFC19B\" width=\"100%\">\n";
        echo "<tr><td>Waffenfertigkeiten</td></tr>";             
        echo "</table>";
        echo "<table width=\"100%\" bgcolor=\"#FFC19B\">";
        echo "<tr><td></td><td>Waffe</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\"></td></tr>";
        $i=0;
        while ($_GET["SELWAF"][$i]){
        echo 
           "<tr>\n",
           "<td align=\"right\">",$i+1,".</td>\n",
           "<td><INPUT type=\"text\" class=\"must\" name=\"WAFFE[NAME][",$i,"]\" value=\"",htmlentities(utf8_decode($_GET["SELWAF"][$i])),"\" readonly></td>\n",
           "<td align=\"right\">+</td>\n",
           "<td><INPUT type=\"text\" class=\"must\" name=\"WAFFE[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>\n",
           "<td><INPUT type=\"text\" class=\"may\" name=\"WAFFE[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>\n",
           "</tr>\n";
         $i++;
        }
        if ($AnzEWaf >0){
        echo "<tr><td></td><td>Waffe</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\"></td></tr>";
        for ($j=0; $j<$AnzEWaf; $j++){
          echo "<tr>",
                "<td align=\"right\">",$i+1,".</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"WAFFE[NAME][",$i,"]\" size=\"30\" maxlength=\"50\"></td>",
                "<td>+</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"WAFFE[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td><INPUT type=\"text\" class=\"may\" name=\"WAFFE[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td></td>",
               "</tr>\n";    
          $i++;
        }
        }
        echo "</table>";
        echo "\n<table bgcolor=\"#FFC19B\" width=\"100%\">\n";
        echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>";             
        echo "</table>";
        echo "<table width=\"100%\" bgcolor=\"#FFC19B\">";
        echo "<tr><td></td><td>Waffen&nbsp;Grundkenntnisse</td><td></td><td></td><td></td><td width=\"100%\"></td></tr>";        
        echo "<tr>",
              "<td></td>",
              "<td>",
                "<select class=\"must\" name=\"WAFFEGK[]\" size=\"3\" multiple>",
                  "<option>Armbrust</option>",
                  "<option>Blasrohr</option>",
                  "<option>B&ouml;gen</option>",
                  "<option>Einhandschlagwaffe</option>",
                  "<option>Einhandschwert</option>",
                  "<option>Fesselwaffe</option>",
                  "<option>Garotte</option>",
                  "<option>Kampf ohne Waffen</option>",
                  "<option>Kampfstab</option>",
                  "<option>Kettenwaffe</option>",
                  "<option>Kharrata</option>",
                  "<option>Namisritra</option>",
                  "<option>Parierwaffe</option>",
                  "<option>Peitsche</option>",
                  "<option>Schild</option>",
                  "<option>Schleuder</option>",
                  "<option>Spie&szlig;waffe</option>",
                  "<option>Stangenwaffe</option>",
                  "<option>Stichwaffe</option>",
                  "<option>Stielwurfwaffe</option>",
                  "<option>Werfen</option>",
                  "<option>Wurfmesser</option>",
                  "<option>Wurfpfeil</option>",
                  "<option>Wurfscheibe</option>",
                  "<option>Wurfspie&szlig;</option>",
                  "<option>Zauberst&auml;be</option>",
                  "<option>Zweihandschlagwaffe</option>",
                  "<option>Zweihandschwert</option>",
                 "</select>",
               "</td>",   
               "<td></td>",
               "<td></td>",
               "<td></td>",
               "<td><font size=\"-1\">(f&uuml;r Mehrfachauswahl &#060;STRG&#062;-Taste gedr&uuml;ckt halten)</font></td>",
              "</tr>\n";    
        echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>\n";
        echo "</table>"; 
//
//      SPRACHEN         
//        
        echo "\n<table bgcolor=\"#C8FFC9\" width=\"100%\">\n";
        echo "<tr><td>Sprachen &amp; Schriften</td></tr>";             
        echo "</table>";       
        echo "<table width=\"100%\" bgcolor=\"#C8FFC9\">";
        echo "<tr><td></td><td>Muttersprache</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\"></td></tr>\n";
        echo "<tr>",
                "<td></td>",
                "<td>",
                "<select name=\"MSPRACHE\" size=\"1\">",
                "<option>Albisch</option>",
                "<option>Altoqua</option>",
                "<option>Aranisch</option>",
                "<option>Asadi</option>",
                "<option>Berekusch</option>",
                "<option>Bulugi</option>",
                "<option>Chryseisch</option>",
                "<option>Comentang</option>",
                "<option>Dunathisch</option>",
                "<option>Dunkle Sprache</option>",
                "<option>Dvarskar</option>",
                "<option>Eldalyn</option>",
                "<option>Erainnisch</option>",
                "<option>Ferangah</option>",
                "<option>Feuerinseldialekte</option>",
                "<option>Ffomorisch</option>",
                "<option>Gnomenon</option>",
                "<option>Halftan</option>",
                "<option>Hochcoraniaid</option>",
                "<option>Hurritisch</option>",
                "<option>Ikengadialekte</option>",
                "<option>KanThaiTun</option>",
                "<option>Kelwisch</option>",
                "<option>Luwisch</option>",
                "<option>L&auml;inisch</option>",
                "<option>Maralinga</option>",
                "<option>Medjisisch</option>",
                "<option>Meketisch</option>",
                "<option>Minangpahitisch</option>",
                "<option>Moravisch</option>",
                "<option>Nahuatlanisch</option>",
                "<option>Neu-Vallinga</option>",
                "<option>Rawindi</option>",
                "<option>Scharidisch</option>",
                "<option>Stammesdialekte</option>",
                "<option>Tegarisch</option>",
                "<option>Toquinisch</option>",
                "<option>Trll'ng</option>",
                "<option>Tuskisch</option>",
                "<option>Twyneddisch</option>",
                "<option>Vallinga</option>",
                "<option>Waelska</option>",
               "</select>",
                "</td>",
                "<td>+</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"WMSPRACHE\" size=\"2\" maxlength=\"2\"></td>",
                "<td><INPUT type=\"text\" class=\"may\" name=\"PMSPRACHE\" size=\"2\" maxlength=\"2\"></td>",
                "<td></td>",
              "</tr>\n";
        echo "<tr><td></td><td>Sprache</td><td></td><td>Wert</td><td>PP</td><td></td></tr>\n";
        $i=0;
//        for ($i=0; $i<$AnzSpra; $i++)
        while ($_GET["SPRACHE"][$i]) {
          echo "<tr>",
                "<td align=\"right\">",$i+1,".</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"SPRACHE[NAME][",$i,"]\" value=\"",htmlentities(utf8_decode($_GET["SPRACHE"][$i])),"\" readonly></td>\n",
                "<td>+</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"SPRACHE[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td><INPUT type=\"text\" class=\"may\" name=\"SPRACHE[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td></td>",
               "</tr>\n";
          $i++;
        }        
        echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></td>";
        if ($_GET["AnzESpra"] >0){
        echo "<tr><td></td><td>Sprache</td><td></td><td>Wert</td><td>PP</td><td></td></tr>\n";
        for ($j=0; $j<$_GET["AnzESpra"]; $j++){
          echo "<tr>",
                "<td align=\"right\">",$i+1,".</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"SPRACHE[NAME][",$i,"]\" size=\"30\" maxlength=\"50\"></td>",
                "<td>+</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"SPRACHE[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td><INPUT type=\"text\" class=\"may\" name=\"SPRACHE[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td></td>",
               "</tr>\n";    
          $i++;
        }        
        echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></td>";
        }
        echo "</table>";
        if ($AnzSchri >0) {
         echo "<table bgcolor=\"#C8FFC9\">";
         echo "<tr><td></td><td>Schriften</td><td></td><td>Wert</td><td>PP</td><td width=\"100%\">Alphabet</td></tr>";
         for ($i=0; $i<$AnzSchri; $i++){
          echo "<tr>",
                "<td align=\"right\">",$i+1,")</td>",
                "<td>",
                 "<select name=\"SCHRIFT[NAME][",$i,"]\" size=\"1\">",                 
                 "<option>Albisch</option>",
                 "<option>Altoqua</option>",
                 "<option>Aranisch</option>",
                 "<option>Asadi</option>",
                 "<option>Baumrunen Beth-Luis-Nion</option>",
                 "<option>Bulugi</option>",
                 "<option>Chryseisch</option>",
                 "<option>Comentang</option>",
                 "<option>Dunathisch</option>",
                 "<option>Dunkle Sprache</option>",
                 "<option>Dvarskar</option>",
                 "<option>Eldalyn</option>",
                 "<option>Erainnisch</option>",
                 "<option>Ferangah</option>",
                 "<option>Futhark</option>",
                 "<option>Halftan</option>",
                 "<option>Hochcoraniaid</option>",
                 "<option>Hurritisch</option>",
                 "<option>KanThaiTun(1)</option>",
                 "<option>KanThaiTun(2)</option>",
                 "<option>KanThaiTun(3)</option>",
                 "<option>KanThaiTun(4)</option>",
                 "<option>KanThaiTun(5)</option>",
                 "<option>KanThaiTun(6)</option>",
                 "<option>Kelwisch</option>",
                 "<option>L&#228;inisch</option>",
                 "<option>Luwisch</option>",
                 "<option>Maralinga</option>",
                 "<option>Medjisisch</option>",
                 "<option>Meketisch</option>",
                 "<option>Minangpahitisch</option>",
                 "<option>Moravisch</option>",                 
                 "<option>Nahuatlanische Bilderschrift</option>",
                 "<option>Nahuatlanische Knotenschrift Quipu</option>",
                 "<option>Neu-Vallinga</option>",
                 "<option>Rawindi</option>",
                 "<option>Scharidisch</option>",
                 "<option>Tegarisch</option>",
                 "<option>Toquinisch</option>",
                 "<option>Tuskisch</option>",
                 "<option>Twyneddisch</option>",
                 "<option>Vallinga</option>",
                 "<option>Waelska</option>",
                 "<option>Zwergenrunen Futhark</option>",
                "</select>",
                "</td>",
                "<td>+</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"SCHRIFT[WERT][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td><INPUT type=\"text\" class=\"may\" name=\"SCHRIFT[PP][",$i,"]\" size=\"2\" maxlength=\"2\"></td>",
                "<td>",
                 "<select name=\"SCHRIFT[ALPHABET][",$i,"]\" size=\"1\">",
                  "<option>Valianisches Alphabet</option>",
                  "<option>Aranische Silbenschrift</option>",
                  "<option>Arracht-Versalien</option>",
                  "<option>Baumrunen Beth-Luis-Nion</option>",
                  "<option>Bulugische Bilderschrift</option>",
                  "<option>Coraniaid-Alphabet</option>",
                  "<option>Futhark</option>",
                  "<option>Hurritische Keilschrift</option>",
                  "<option>KanThaiTun(1)</option>",
                  "<option>KanThaiTun(2)</option>",
                  "<option>KanThaiTun(3)</option>",
                  "<option>KanThaiTun(4)</option>",
                  "<option>KanThaiTun(5)</option>",
                  "<option>KanThaiTun(6)</option>",
                  "<option>L&auml;inisch</option>",
                  "<option>Meketische Bilderschrift</option>",
                  "<option>Nahuatlanische Bilderschrift</option>",
                  "<option>Nahuatlanische Knotenschrift Quipu</option>",
                  "<option>Rawindisches Alphabet</option>",
                  "<option>Tegarisch</option>",
                  "<option>Toquinische Keilschrift</option>",
                  "<option>Tuskische Keilschrift</option>",
                  "<option>Waelska</option>",
                  "<option>Zwergenrunen Futhark</option>",
                 "</select>",
               "</tr>\n";
         }
         echo "<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>\n";
         echo "</table>";
                 
        }
        
        if ($_GET["SELZAU"][0] OR $_GET["AnzEZaub"] OR $_GET[SELZAUBZ][0]) {
        
         echo "<div style=\"background-color:#9CACE8\">Zauberer\n";
         echo "<table bgcolor=\"#9CACE8\">";
         
         echo 
           "<tr>",
            "<td></td>",
            "<td></td>",
            "<td></td>",
            "<td>",
             "<select name=\"SPEZG\" size=\"1\">\n",
             "<option>Spezialgebiet</option>",
             "<option>Adept der Herrschaft</option>",
             "<option>Adept der Bewegung</option>",
             "<option>Adept der Erkenntnis</option>",
             "<option>Adept der Sch&#246;pfung</option>",
             "<option>Adept der Ver&#228;nderung</option>",
             "<option>Adept der Wandlung</option>",
             "<option>Adept der Zerst&#246;rung</option>",
             "<option>Erdmagier</option>",
             "<option>Feuermagier</option>",
             "<option>Luftmagier</option>",
             "<option>Wassermagier</option>",
             "<option>Eismagier</option>",
             "<option>Adept der g&#246;ttlichen Ordnung</option>",
             "<option>Adept des formbaren Chaos</option>",
             "<option>Adept des Todes</option>",
//            "<option>Prim&#228;r- und Sekund&#228;relement</option>",
//            "<option>Eis Erde</option>",
//            "<option>Erde Eis</option>",
//            "<option>Eis Wasser</option>",
//            "<option>Wasser Eis</option>",
//            "<option>Erde Feuer</option>",
//             "<option>Feuer Erde</option>",
//             "<option>Feuer Luft</option>",
//             "<option>Luft Feuer</option>",
//             "<option>Luft Wasser</option>",
//             "<option>Wasser Luft</option>",
            "</select>",
            "</td>",
            "<td></td>",
            "<td></td>",
           "</tr>";
         echo "</table>";
         if ($_GET["SELZAU"][0]) {
         echo "<table bgcolor=\"#9CACE8\">";
         echo "<tr><td></td><td>Zauberfertigkeiten</td><td></td><td></td><td></td><td width=\"100%\"></td></tr>";
         $i=0;
         while ($_GET["SELZAU"][$i]){
          echo 
           "<tr>\n",
           "<td align=\"right\">",$i+1,".</td>\n",
           "<td><INPUT type=\"text\" class=\"must\" name=\"ZAUBER[NAME][",$i,"]\" value=\"",htmlentities(utf8_decode($_GET["SELZAU"][$i])),"\" readonly></td>\n",
           "<td align=\"right\"></td>\n",
           "<td></td>\n",
           "<td></td>\n",
           "</tr>\n";
         $i++;
         }
         }
         if ($_GET["SELZAUBZ"][0]) {
         echo "<tr><td></td><td>Zauberfertigkeiten</td><td></td><td></td><td></td><td>Zusatz</td></tr>";
         for ($h=0; $h<$AnzZaubZ; $h++){
          
          echo 
            "<tr>\n",
            "<td align=\"right\">",$i+1,".</td>\n",
            "<td><select name=\"ZAUBER[NAME][",$i,"]\" size=\"1\"\>\n";
            $j=0;
            while ($_GET["SELZAUBZ"][$j]){
              echo "<option>",htmlentities(utf8_decode($_GET["SELZAUBZ"][$j])),"</option>\n";
              $j++;
            }           
          echo
            "</select>\n",
            "<td></td>",
            "<td></td>",
            "<td></td>",
            "<td><INPUT type=\"text\" class=\"must\" name=\"ZAUBER[ZUSATZ][",$i,"]\" size=\"30\" maxlenght=\"30\"></td>",
            "</tr>\n";
          $i++;
        }         
        }
        if ($_GET["AnzEZaub"] >0) {
         echo "<tr><td></td><td>Zauberfertigkeiten</td><td></td><td></td><td></td><td>Zusatz</td></tr>";
          for ($j=0; $j<$AnzEZaub; $j++){
           echo "<tr>",
                "<td align=\"right\">",$i+1,".</td>",
                "<td><INPUT type=\"text\" class=\"must\" name=\"ZAUBER[NAME][",$i,"]\" size=\"30\" maxlength=\"50\"></td>", 
                "<td></td>",
                "<td></td>",
                "<td></td>",
                "<td><INPUT type=\"text\" class=\"may\" name=\"ZAUBER[ZUSATZ][",$i,"],\" size=\"30\" maxlength=\"50\"></td>",
               "</tr>\n";
            $i++;
          }
          echo "</table>";
        }
           echo "\n<table bgcolor=\"#9CACE8\" width=\"100%\">\n";
        echo "<tr><td>&nbsp;</td></tr></td></tr>";
        echo "</table>";
        echo "</div>";
        }
    ?>  
    </td>
  </tr>   
</table><br>
  Wenn MAGuS installiert ist, kann die Figur automatisch in MAGuS ge&ouml;ffnet werden (Unter Sicherheitsaspekten
  nicht zu empfehlen). Die Figur kann dann direkt in MAGuS weiterverarbeitet werden.<br> 
  Alternativ kann der eingegebene Abenteurer auf der Festplatte gespeichert werden. Die Datei 
  wird unter dem Namen &quot;MAGuS-Charakter.magus&quot; abgespeichert. Diese Datei kann dann in MAGuS 
  ge&ouml;ffnet und weiter bearbeitet werden.<br>
  <input type="submit" value=" Fertigstellen ">
  <input type="reset" value=" Eingabe zur&uuml;cksetzen ">
</FORM>
</body>
</html>



