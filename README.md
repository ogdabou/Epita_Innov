Liens Utiles
===========
Mise en place + Présentation d'OPENCV
http://fr.openclassrooms.com/informatique/cours/introduction-a-la-vision-par-ordinateur/presentation-d-opencv

Lire un flux vidéo/webcam avec OpenCV
http://www.esiee.fr/~kachourr/Page_web/Enseignement/2012_2013/EL5E13/RK_EL5E13-TP3&4_2012-13

Face detector with OPENCV
http://www.cs.princeton.edu/courses/archive/fall08/cos429/CourseMaterials/Precept1/facedetect.pdf

Problemes websocket et réseau télécoms (3g & autres..)
http://blog.hekkers.net/2012/12/09/websockets-and-mobile-network-operators/


# PARTIE PC :
-Pouvoir détecter les zones clés (portes, fenêtres...)
Le but serait de pouvoir configurer l'application via son PC, le prof nous a parler de lib pour détecter les zones à risques (portes, fenêtres), certaines libs proposent cela.

**-Pouvoir détecter un mouvement**
Juste un signal "Il y a du mouvement !" jusque "Un mouvement se dirige dans telle direction", ça devrait pouvoir se faire. Et encore, si possible, pouvoir définit les direction à checker (déssiner une ligne, l’enregistrer, et le logiciel regarde si un truc se déplace suivant cette ligne par exemple). Prendre des photos quand on detecte du mouvement. Dans les deux cas (un mouvement ou carrément une direction), il faudra présenter dans le rapport avec des images etc... Faut se dire qu'on peut présenter même une détection simple et aller faire du plus compliqué :).

**-Pouvoir détecter un visage, et prendre des photos** zoomées dessus pourrai être une bonne idée.

**-Pouvoir détecter un mouvement**

**-Avoir un comportement spécifique selon l'heure ou le temps.** Par exemple, si il fait nuit, l'appli se met en mode nuit, et pourra par exemple à # détecter la présence de lumières type lampe torche (lumières très directionnelle).

**-Pour le capteur de profondeur :** Je sais pas trop ce qui pourrais etre utile, ca doit etre plus simple au niveau API de détecter les déplacement, mais je suis meme pas sur, on devrait pouvoir se passer de la kinect, et meme de la webcam, pendant un bon moment ! :) (flux vidéo pris avec le téléphone oue une caméra.. ou sur le web osef)

**-Zone clés :** Pouvoir définir des zones clés pour lesquelles faire attention. (Pouvoir faire un rapport pour dire que l'intru est aller dans telle zone clé). _Rien que pouvoir définir des zone clés serait pas mal, même si la fonctionnalité de détecter si quelqu'un est entré dedans ne marche pas :)._

**-Zone clés + mouvements :** On peut aller plus loin encore... définir des zone clés ET les marqués comme "pièces de la maison", détecter si l'intru sest déplacer dans la zone clé et à disparu, en déduire que la personne est dans la piece.. calculer le temps qu'il y est resté etc.. Bref, faire quelque chose de paramétrable, quand on défini une zone, pouvoir avoir des types "fenetre, porte" et définir des actions (quand personne entre dedans, mesurer temps pour qu'il en sorte, ou mesurer temps qu'il reste dans la piece) que ce soit modulable quoi.

**-Voir si il est possible de détecter des animaux,** si oui, alors essayer de faire une configuration ou on pourrai rajouter "oui j'ai un chat", que l'appli propose de vérifier qu'elle le détecte..

**-Définir une stratégie de sauvegarde : **Sauvegarder du flux vidéo, c'est très lourd, donc sur une longue durée... Donc voir ce qui se passerai, l'appli sauvegarde que quand elle détecte un mouvement ? Un visage ? Stratégie de néttoyage automatique du répertoire apres X temps (proposer a l'utilisateur de garder les vidéos pour X jours). Ou pouvoir marquer les vidéo comme "importante" et dans ce cas elles ne seraient pas supprimées. Définir une stratégie veux dire qu'on peut la coder aussi hein ^^. Quelqu'un peut s'occuepr de prendre des screenshots d'un flux vidéo etc..

**-Définir une stratégie d'events ! **Quand on détecte un visage et un intru, lancer un event sur l'application smartphone, pouvoir les configurer.
Par exemple : définir si on veux recevoir une notification sur l'appli portable, ou recevoir un mail, ou un sms.


# L'application SMARTPHONE :
Comme on l'a dis, ce serait cool d'avoir une appli sur son tel!

-**Notifier l'utilisateur quand il y a détection d'intru**

-**Proposer a l'utilisateur d'ouvrir le flux vidéo de sa caméra**

-**Proposer à l'utilisateur de prendre des screenshots**

-**Proposer à l'utilisateur d'appeler la police**

-**Pouvoir synchroniser les parametre de l'appli pc et les changer**

-**Pouvoir accéder au flux vidéo de sa webcam a tout moment** (y rajouter des cadres lors de détection peut etre cool, comme sur les appareil photos)

***

Ce weekend, venez en permanence sur Skype (bon a part pendant le cours de maths xD).
On ne sait pas le temps que prendra chaque tâches.. mais si vous prenez la notification sur l'appli quand ya un intru... Essayer dans un premier temps d'envoyer une notif. Quand ca c'est terminé, bah prendre la détection d'intru si personne l'a pris :D.
