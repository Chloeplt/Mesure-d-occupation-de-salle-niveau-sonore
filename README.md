# RAPPORT PROJET IOT 2022/2023
# Mesure d'occupation de salle et de niveau sonore

## Aide a la mise en forme 

## Objectif - Chloe & Léo

L’objectif de notre projet est de mesurer de taux d'occupation d'une salle, ansi que son niveau sonore. La communication se fera avec un protocole Wifi et permettra de transmettre des payloads lourd dans un périmètre restraint.
Notre produit peut avoir de multiple utilité et donc de multiple client potentiel.

- Pour les salles de réunions des entreprises 

- Pour les bibliothèques

- Pour les supermarchées 

- Pour les salle de concert, bar, salle de sport ect



![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/exemple_d'utilisation_projet_iot.png?raw=true)

### Voci la brochure commercial de notre produit :
#### L'exterieur de la brochure 
![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/exte_brochure.jpg?raw=true)
#### L'interieure de la brochure 
![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/inte_brochure.jpg?raw=true)

Une vidéo de démonstration est disponible ici.

https://drive.google.com/drive/folders/181wm0XhsHDg3s_iM2QxCAcid1apHPN5r?usp=share_link

## Analyse de marché

Les capteurs d'occupation de salle et de confore sonore sont presque exclusivement adressé au entreprise. Pour avoir accès à des information supplémentaire sur les poduit, il faut **impérativement faire un devis** au nom de son entreprise. Il est donc très difficile de faire une analyse de marché pour pouvoir comparé notre produit.
Néamoins, nous avons trouvé quelques concurrent potentielle :

| Marque          | Avantage(s)                                                | Inconvénient(s)                                                                     | 
|-----------------|------------------------------------------------------------|-------------------------------------------------------------------------------------|
| Wx Company      | Capteur température/qualité de l'air, Application mobile   | Pas d'écran sur la porte, Pas de capteur de confort sonore                          |
| ubigreen        | Bas débit LPWAN, Site web/Application mobile               | Capteur sous les tables, Pas d'écran sur la porte, Pas de capteur de confort sonore | 
| spaceti         | Durée de vie batterie - Jusqu'à 15 ans                     | Uniquement PIR sensor, pas d''cran sur la porte, pas de capteur de confort sonore   | 
| XPAIR           | Caméra thermique (anonymat), BLE, mesure du confort sonore | Pas d'ecran sur la porte                                                            | 


On remarque que le desavantage commun de tout nos concurrents est **l'absence d'un écran tel que notre Wio terminal au niveau des portes des salles de réunion**. Nous devons donc mettre en avant cette différence afin de vendre au mieux notre produit.

## Architechture globale du système

Le système est composé d’un **WIO Terminal**, d’un **ESP32-EYE** et d’un **capteur de présence PIR**. 
 L’**ESP32-EYE** est un capteur embarquant une **caméra** et un **microphone**. Il communiquera avec le **Wio Terminal** grâce au protocole **Wifi**. Le **capteur PIR** sera utilisé pour **détecter la présence** de quelqu’un et communiquera directement avec le **Wio Terminal** sur lequel il sera branché. Enfin nous utiliserons des éléments directement présent sur le **Wio Terminal** tel qu’une **LED**, des **boutons** pour avoir **plusieurs mods de fonctionnement** (mode normal, mode économie d'énergie, mode débugage), ainsi que l’écran d’affichage si besoin, cela dépendra de l’autonomie souhaité et du mode en cours d’utilisation. Pour le mode normal il sera possible d’afficher des données en temps réel et l’écran pourra être utile pour le mode débugage car on pourra afficher plus de variables.
 
 Le principe de fonctionnement est le suivant. Lorsque le **capteur de présence PIR** détecte un mouvement, il **allume la caméra et la lumière**. Cette dernière est ici représentée par la LED du Wio Terminal. La caméra (embarqué sur l’ESP32-EYE) prend alors le relais pour détecter la présence d’individus. Elle prend une photo toutes les minutes (pour diminuer la consommation) et tant que des individus sont détectés, elle transmet au **terminal WIO le nombre de persones** présentent dans la pièce. Tant qu’il y a détection, la lumière reste allumée et le confort sonore ainsi que le nombre de persones de la pièce sont indiqué. Le **confort sonore** est mesuré par l’ESP32-EYE grâce à un **micro intégré** qui relèvera l’intensité sonore. Si il est trop haut la **LED clignotera** pour avertir les personnes présentes. A noter qu'ici la LED n’est pas très voyante mais on pourra par la suite en ajouter une externe qui sera plus voyante. Lorsque plus **personne n’est détectée**, la caméra et la lumière s’éteignent et le capteur de présence reprend sa détection. 
 L’avantage d’une caméra avec détection d’individus comparé à un détecteur de mouvement/présence est que même si la personne ne bouge pas, elle reste détectée. Qui ne s’est jamais retrouvé sans lumière aux toilettes et à du agiter les bras afin de voir quelque chose ?
 
Notre modèle embarquera 3 mods différents.
 Le **mode** de fonctionnement **normal** fonctionne comme expliqué ci-dessus. Il affiche sur l’écran du terminal WIO le confort sonore et le taux d’occupation lorsque des personnes sont détectées. Si fait clignoter la LED si l’intensité sonore est trop haute.
 Le **mode économie d’énergie** n’utilisera pas l’écran afin de consommer moins de ressources. La LED clignotera toujours si l’intensité sonore est trop haute et embarquera une fonctionnalité supplémentaire. Cette dernière est l’utilisation d’un détecteur de luminosité au dos du terminal. Si on choisit de fixer le terminal sur une fenêtre, on pourra détecter si la lumière du soleil est assez forte et dans le cas échéant il ne sera pas nécessaire d’allumer la lumière.
Enfin le **mode débogage** affichera plus d'informations sur l’écran si on a besoin de vérifier le fonctionnement des différents capteurs et fera clignoter la LED.
On pourra aussi définir un mode supplémentaire de surveillance, celui-ci serait actif en dehors des plages d’utilisations de la salle/pièce. Le fonctionnement serait similaire à celui du mode économie d’énergie mais si quelqu’un est détecté, la caméra prendra en photo l’individu toutes les 5 secondes et cette photo sera envoyée par wifi, on pourra se connecter avec un ordinateur au wifi pour récupérer ses différentes photos en temps réel.

### Changements de comportement de l’objet en fonction des événements
![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/diagramme_automate.png?raw=true)


## Sécurité globale

Nous utilisons un protocole Wifi pour communiquer entre notre ESP-EYE et notre Wio Terminal. Afin d’assurer une sécurité optimale de notre système il faut :

-	Mettre en place une **clé de chiffrement de 256 bits**. Nous utilisons une clé de chiffrement très forte car les données transmissent sont très sensible, nous voulons donc maximiser la sécurité. Cette première étape permet de lutter contre les attaques de force brute.

-	Utiliser le **protocole de sécurité WPA2**(Wifi Protected Access) qui utilise un chiffrement AES(Advanced Encryption Standard), afin de lutter contre les attaques de type « meet in the middle ».

Un **SSID** et un **mot de passe** seront d’ores et déjà configuré dans le système et ne pourront être visible et modifiable qu’avec un mot de passe.


## Respect de la vie privée du service 

Pour la **caméra**, le **micro** et le **capteur de détection PIR**, le principal risque d’atteinte au respect de la vie privée provient d’une possible déduction d’informations sur les activités et les habitudes de vie des personnes dans l'environnement **surveillé**. 

Cela pourrait survenir si quelqu’un parvient à **prendre le contrôle** ou à **récupérer les informations** des différents capteurs. Cependant les capteurs n’offrent pas les mêmes informations. Le capteur de présence sera limité à savoir les habitudes de présence dans l’environnement surveillé. Le micro est seulement utilisé pour **mesurer le volume sonore**, il peut donc fournir la même information que le capteur de présence. 

Cependant, si quelqu’un arrive à **flasher un autre code** par dessus, il pourrait avoir accès aux **conversations présentes dans la pièce**. Enfin la caméra pourra offrir une information supplémentaire à la présence ou non d’individus, celle de l’**image**. Une personne pourra donc potentiellement récupérer les photos envoyées par la caméra si il arrive à s’y connecter et changer le code ou alors si il parvient à **se connecter au wifi**, que la caméra est dans le mode surveillance et que quelqu’un est détecté (donc en dehors des horaires d’utilisation de la pièce/salle.

Des mesures peuvent être prises pour **avertir les utilisateurs** ou **diminuer les risques**. Le principal moyen de diminuer les risques est de rajouter un **chiffrement des données** en plus de la **sécurité du Wifi**. Un autre moyen serait de rendre l’accès au dispositif plus dur. Par exemple en le **dissimulant**, en le disposant en hauteur ou en confectionnant un boîtier supplémentaire pour compliquer une connexion au hardware.

Pour la partie avertissement des utilisateurs, leur diffuser une **politique de confidentialité**, leur faire signer des **conditions d’utilisations** ou demander leur accords si le cadre est privé peuvent être une possibilité.


## Architecture matérielle de l'objet - Chloé

![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/Architecture_Materielle.png?raw=true)

## Coût de la BOM du produit

| Matériel        | Quantité | Prix unitaire      | Prix total       |
|-----------------|----------|--------------------|------------------|
| Wio Terminal    | 1        | 30,9               | 154500           |
| PIR motion sensor| 1       | 6,1                | 30500            |
| ESP32-EYE       | 1        | 22,5               | 112500           |
| LED             | 1        | 0,0447             | 223,5            |
| Système complet | 5000     | 59,5447            | 297723,5         |


Note : les prix indiqués sont en *$*


## Coût de certification ETSI du produit

Le cout de la certification ETSI dépend principalement des normes ETSI appliqué à notre produit. Mais il est assez difficile d’avoir une idée précise du prix. En effet, le cout dépend aussi de nombreux autres facteurs tels que la complexité du produit, le nombre de tests requis et les coûts administratifs associés à la certification. 

Le Wio terminal utilise des bandes passantes de fréquences 2.4 GHz, nous pouvons donc en déduire certaine norme applicable à notre produit :

-	**EN 300 328:** Cette norme spécifie les exigences pour l'utilisation des bandes de fréquences de 2,4 GHz pour les dispositifs sans fil dans l'Union Européenne. Cette norme couvre les exigences de compatibilité électromagnétique (CEM) et de sécurité pour les dispositifs sans fil utilisant ces bandes de fréquences.

-	**EN 301 489-1:** Cette norme spécifie les exigences pour l'immunité électromagnétique pour les équipements terminaux et les équipements réseau utilisés dans les systèmes de communication électronique.

-	**EN 301 489-17:** Cette norme spécifie les exigences pour la sécurité des équipements terminaux et des réseaux utilisés dans les systèmes de communication électronique.

-	**EN 303 645:** Cette norme spécifie les exigences de sécurité pour les objets connectés (smart-objects) utilisant les technologies de communication radio. 

Les certifications coutent en moyenne 800€ pour 3 ans de validité. On peut donc estimer un **total de 1067€/ans.**


## Trame Wi-FI

Dans notre cas, notre Wio Terminal est un point d'accès Wi-Fi et notre ESP32-EYE est une station.
Wio Terminal utilise la version 2.4GHz de la norme WiFi (IEEE 802.11b/g/n). Les types de trames WiFi (802.11b/g/n) sont :

### Trame de management (Management frame) : 
- Beacon: utilisé par les points d'accès pour annoncer leur présence sur le réseau.
- Probe request: utilisé par les stations pour rechercher des points d'accès disponibles.
- Probe response: utilisé par les points d'accès pour répondre aux demandes de sondes.
- Association request: utilisé par les stations pour demander à s'associer à un point d'accès.
- Association response: utilisé par les points d'accès pour accepter ou refuser les demandes d'association.

### Trame de contrôle de liaison (Control frame) 

- RTS (Request to send) : utilisé pour demander l'accès au support pour envoyer des données.
- CTS (Clear to send) : utilisé pour donner l'autorisation de transmettre des données.
- ACK (acknowledgment) : utilisé pour indiquer la réception réussie d'une trame de données.

### Trame de données (Data frame) : 
Utilisée pour transmettre des données utiles entre les stations.
Dans notre cas, le nombre de personne presente dans la pièce, le niveau sonore, et potentiellement des photos.

## Logiciel embarqué de l'objet

Pour le langage de programmation, nous avons choisi d'utiliser **Arduino**. Même si ce n'est pas le plus optimisé ni celui qui consomme le moins, nous le trouvions utile dans le **cadre de ce projet**. Les **points négatifs** du langage **Arduino** tels que sa **capacité de stockage limitée** ou sa **taille mémoire** ne posaient **pas de problème** ici. 

En effet, ce dernier permet une **prise en main rapide** et possède une s**yntaxe proche du C**, un langage que nous avons beaucoup utilisé. En plus de cela, de nombreux projets et **exemples** sont **disponibles en ligne**, ce qui est pratique dans le cadre de ce projet où le but n'était pas de coder l'intégralité du projet mais plutôt de réutiliser des bouts de code ici et là afin de faire fonctionner tous les objets ensemble. Enfin, **Arduino** était **compatible** avec l'**ensemble de nos objets**, ce qui rendait la chose **pratique** car devoir jongler entre plusieurs langages de programmation n'est pas le plus évident.


## Métrique logiciel

### Coté Wio Terminal :
Fichier **Wio_Terminal_code.ino** :
* **Taille du fichier : 9.88 Ko**
* **128 lignes de code**
* **39 lignes de commentaires**
* **5 variables déclarées** (pir_detection, sonor_lvl_high, nb_occupant, mode, first_eco)
* **14 fonctions déclarées** (setup, loop, mode_demarage, mode_normal, mode_eco, mode_debug, start_screen, passage_mode_normal, passage_mode_eco, passage_mode_debug, _Too_loud_from_micro, _Not_Too_loud_from_micro, _No_PeopleDetected_PIR, _PeopleDetected_PIR)
* **5 #define utilisés** (PIR_MOTION_SENSOR, LCD_BACKLIGHT, TFT_eSPI, Free_Fonts, TFT_eSprite)
* **2 include utilisés** (TFT_eSPI, Free_Fonts)

Fichier **Free_Fonts.h** :
* **Taille du fichier : 9.91 Ko**
* **91 lignes de code**
* **85 lignes de commentaires**
* **24 #define utilisés**

## Alimentation du produit

La comsommation de notre produit est consequente, ceci du fait des transmission de donnée via le Wi-Fi et de l'utilisation d'une caméra. Pour la camera, nous avons donc decidé de ne pas utiliser de batterie mais de **brancher notre système directement au secteur** en utilisant un adaptateur **Micro-USB (5V, 3A)**. Etant donnée que la camera sera contre un mur ou au plafond, ça ne sera pas derangeant pour l'utilisation.

Pour ce qui est du Wio Terminal, Nous utilisons le module ajoutant une **batterie LiPo de 650 mAh**. Cette batterie à une **autonomie de 7h en utilisation continue**. Il est donc demander à l'utilisateur de le brancher tous les soirs.

## Analyse du cycle de vie du produit

L'analyse du cycle de vie d'un produit prend en compte plusieurs critères comme, l'extraction des matières premières, la production, l'utilisation, la fin de vie et le recyclage.

### l'extraction des matières premières
Notre produit est fabriqués à partir de **métaux rares et de matières plastiques**. Il faudrait que ces matières premières sont extraites de manière responsable pour minimiser l'impact environnemental.

### La production du produit 
Ceci implique l'assemblage des différents composants électroniques. Ce qui peut générer des **déchets électroniques** et des émissions de gaz à effet de serre. Il faudrait que la production se fasse de manière éco-responsable et que les déchets soit correctement gérés.
 
### l'utilisation du produit
Notre produit consomme de l'énergie pour fonctionner. De **l'électricité**, et de la **bande passante**. Il faudrait que l'electricité consommé soit la plus verte possible.

### le recyclage du produit
A la fin de vie de de notre produit, on pourra recycler une grande partie des composants électroniques, mais aussi et surtout la batterie Lipo en la déposant dans un centre de recyclage spécialisé. La batterie est la partie du produit qui est le plus suceptible d'être défectueuse rapidement. On peut compter 200 à 300 cycles de charge/décharge si elle est utilisée et entretenue correctement. Cela signifie qu'utilisée quotidiennement, elle pourrait durer environ **un an ou deux** avant de nécessiter un remplacement. Les autres composant peuvent quand à eu on une durée de vie qui varie **entre 5 et 15 ans** en fonction de leur entretient.



