// --- Programme Arduino --- 
// Trame de code générée par le générateur de code Arduino
// du site www.mon-club-elec.fr 

// Auteur du Programme : X. HINAULT - Tous droits réservés 
// Programme écrit le : 30/03/2015  GPLv3 

// ////////////////////  PRESENTATION DU PROGRAMME //////////////////// 

// -------- Que fait ce programme ? ---------
 /*Un servomoteurs connectés à la carte Arduino est contrôlé
à partir du PC (interface Processing)

Controle par chaine de la forme : 
* servoPan(000) avec 000 = angle absolu en degrés pour un positionnement immédiat
* servoPanto(000) avec 000 = angle absolu en degrés pour un positionnement progressif avec delai vitesse
* servoPantoR(000) avec 000 = angle relatif en degrés pour un positionnement progressif avec delai vitesse
* vitesse(000) avec 000 = delai en millisecondes à utiliser entre 2 positions intermédiaires (10 = rapide, 50 = lent)

*/ 


// --- Fonctionnalités utilisées --- 

// Utilise 2 servomoteurs

// -------- Circuit à réaliser --------- 

// ******* ATTENTION : il est possible de connecter directement 2 ou 3 servomoteurs sur la carte Arduino
// Connecter un servomoteur PAN sur la broche 14
// Connecter un servomoteur TILT sur la broche 15

// /////////////////////////////// 1. Entête déclarative /////////////////////// 
// A ce niveau sont déclarées les librairies incluses, les constantes, les variables, les objets utiles...

// --- Déclaration des constantes ---

// --- Inclusion des librairies ---

#include <Servo.h> // librairie pour servomoteur 
//#include <Utils.h> // librairie personnelle avec pleins de fonctions utiles 
#include <UtilsServo2.h> // librairie personnelle avec des fonctions utiles pour les servomoteurs

// --- Déclaration des constantes utiles ---

// --- Déclaration des constantes des broches E/S numériques ---

//---- broches des servomoteurs --- 

const int nombreServos=2; // nombre de servomoteurs 
int brochesServos[nombreServos]={14,15}; 

const int Pan=0; // indice du servomoteur Pan
const int Tilt=1; // indice du servomoteur Tilt

// --- Déclaration des constantes des broches analogiques ---


// --- Déclaration des variables globales ---

boolean debug=true; // mettre à true si message debug

// buffer de réception = tableau de char
const int sizeMax=64;  // taille max buffer reception 
char buffer[sizeMax];  // tableau de reception des caracteres
int sizeIn;  // nombre de caracteres dans le buffer

long params[6]; // déclare un tableau de long - taille en fonction nombre max paramètres attendus

//------- divers 

long millis0=millis(); // variable de memorisation de de millis

// --- Déclaration des objets utiles pour les fonctionnalités utilisées ---

//----- objets racine pour les librairies incluses 
//Utils utils; 

//UtilsServo utilsServo(nombreServos, brochesServos);  // initialise objet utils servo à partir du nombre de servos et du tableau des broches à utiliser
UtilsServo2 utilsServo(nombreServos);  // initialise objet utils servo à partir du nombre de servos 

// ////////////////////////// 2. FONCTION SETUP = Code d'initialisation ////////////////////////// 
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

void setup()   { // debut de la fonction setup()

// --- ici instructions à exécuter 1 seule fois au démarrage du programme --- 

// ------- Initialisation fonctionnalités utilisées -------  

Serial.begin(115200); // initialise connexion série à 115200 bauds
// IMPORTANT : régler le terminal côté PC avec la même valeur de transmission 

//--- Initialisation Servomoteur 

//------ initialisation des servomoteurs 
utilsServo.anglesServo(Pan,90,90,90); // initialise les angles du servomoteur [0]: angle courant [1] : angle de travail [2]: angle initial 
utilsServo.anglesServo(Tilt,90,90,90); // initialise les angles du servomoteur [0]: angle courant [1] : angle de travail [2]: angle initial 

utilsServo.vitesseServos(20); // fixe la vitesse des servomoteurs - délai entre 2 pas en ms
utilsServo.init(brochesServos); // fonction d'initialisation globale (attache les servos aux broches, met broches en sortie et positionne servo


Serial.println("Arduino OK"); // debug

delay(200);

Serial.println(F("---- Instructions reconnues ----")); // debug
Serial.println(F("")); // debug
Serial.println(F("***** servomoteurs *****")); // debug
Serial.println(F("vitesseServos(xxx) : fixe la vitesse pour instructions To")); // debug
Serial.println(F("etc.")); // debug



} // fin de la fonction setup()
// ********************************************************************************

////////////////////////////////// 3. FONCTION LOOP = Boucle sans fin = coeur du programme //////////////////
// la fonction loop() s'exécute sans fin en boucle aussi longtemps que l'Arduino est sous tension

void loop(){ // debut de la fonction loop()


      inWaiting(); // réception chaine dans buffer - voir ci-dessous 
      
      if (sizeIn!=0){ // si une chaine a été recue
      
        // analyse de chaine avec fonction native avr-c sscanf : http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
        //sscanf(buffer, "chaineatester(%d)", &params[0]) --> n : le nombre d'occurence trouvées 

        // format supporté pour la recherche de chaine : voir ici : http://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm 
        // [^,] : jusqu'à ce qu'il y ait une , seulement si recherche chaine.. 
        // % seul renvoie la valeur ascii
        // %d renvoie les chiffres
        // %s renvoie les chaines
        // %f renvoie les float

        
        if (sscanf(buffer, "servoPan(%d)", &params[0])==1)  Serial.println("Arduino a reconnu servoPan(xxx)"),utilsServo.servo(Pan,params[0]) ;// renvoie n si chaine trouvée
        else if (sscanf(buffer, "servoPanTo(%d)", &params[0])==1)  Serial.println("Arduino a reconnu servoPanTo(xxx)"),utilsServo.servoTo(Pan,params[0]) ;// renvoie n si chaine trouvée
        else if (sscanf(buffer, "servoPanToR(%d)", &params[0])==1)  Serial.println("Arduino a reconnu servoPanTo(xxx)"),utilsServo.servoToR(Pan,params[0]) ;// renvoie n si chaine trouvée
 
        else if (sscanf(buffer, "servoTilt(%d)", &params[0])==1)  Serial.println("Arduino a reconnu servoTilt(xxx)"),utilsServo.servo(Tilt,params[0]) ;// renvoie n si chaine trouvée
        else if (sscanf(buffer, "servoTiltTo(%d)", &params[0])==1)  Serial.println("Arduino a reconnu servoTiltTo(xxx)"),utilsServo.servoTo(Tilt,params[0]) ;// renvoie n si chaine trouvée
        else if (sscanf(buffer, "servoTiltToR(%d)", &params[0])==1)  Serial.println("Arduino a reconnu servoTiltToR(xxx)"),utilsServo.servoToR(Tilt,params[0]) ;// renvoie n si chaine trouvée


        else if (sscanf(buffer, "servosSync(%d,%d)", &params[0], &params[1])==2)  Serial.println("Arduino a reconnu servosSync(xxx,xxx)"),utilsServo.servosSync(params[0],params[1]) ;// renvoie n si chaine trouvée
        else if (sscanf(buffer, "servosSyncR(%d,%d)", &params[0], &params[1])==2)  Serial.println("Arduino a reconnu servosSyncR(xxx,xxx)"),utilsServo.servosSyncR(params[0],params[1]) ;// renvoie n si chaine trouvée
      
      } // fin if sizeIn


} // fin de la fonction loop() - le programme recommence au début de la fonction loop sans fin
// ********************************************************************************

// fin du programme 

//--- fonction de réception de chaine par le port série via tableau de char (plus léger que String)
void inWaiting(){
   
   sizeIn=0; 
   
   while(Serial.available() > 0) {  // tant qu'un caractere dans la file d'attente serie
      char c=Serial.read();  // lecture du caractere suivant
      //Serial.print(c);  // affichage 
      if(sizeIn<sizeMax) buffer[sizeIn++]=c;  // on le memorise dans le buffer tant que place
      //if(buffer[sizeIn-1]==';') break;  // on sort si dernier caractere recu=;
      //if (c==';') break; // equivalent car c est le dernier caractere recu - 
      // on analyse après...
      
      if (Serial.available()==0) delay(5); // laisse temps caractere evntuel d'arriver
      
  } // fin tant que  octet réception
 
} // fin inWaiting
