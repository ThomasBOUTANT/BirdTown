# BIRDTOWN_2017
2D RPG Game created for the C++ lessons

How many time ?
- version 1: 1 month in May/June 2017
- version 2: 2 months between July 2017 and August 2017

The team:
- BOUTANT Thomas
- CHARRUAULT Marie

Context of the project:
- It's a little school project of 2 months, made at the end of the 2nd year at Télécom SudParis, a Top French Engineer School.


We have used Microsoft Visual Studio and the template SFML, plus Tiled Map Editor for the maps, plus XML for the scenarii.





//**************    MANUAL: CONFIGURATION (in French) **************//

Pour lancer le jeu, être en mode "Release" et non "Debug".

Dans C:\Software, il y a les fichiers :

	- SFML-2.4.2 

	- tmxlite    //que vous pouvez trouvez ici : https://github.com/fallahn/tmxlite/tree/master/tmxlite
 
 	- pugixml-1.8

Dans Propriétés du projet BirdTown :

	- Pour "C/C++" -> "Autres répertoires Include", il y a : 

			C:\Software\tmxlite\tmxlite\include;
			C:\Software\SFML-2.4.2\include; 
			C:\Software\pugixml-1.8\src


	- Pour "Editeurs de liens" -> "Général" -> "Répertoires de bibliotheques supplémentaires", il y a :

			C:\Software\SFML-2.4.2\lib;
			C:\Software\tmxlite\tmxlite\bin\ReleaseShared;


	Remarque : il faudra peut-être faire un cmake pour obtenir le fichier /bin de tmxlite...


	- Dans "Editeurs de liens" -> "entrée" -> "Dépendances supplémentaires", il y a :

			libtmxlite.lib; sfml-audio.lib;sfml-graphics.lib;sfml-network.lib;sfml-system.lib;sfml-window.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)

Penser à mettre les fichiers .dll, .pdb, .iobj, .exp dans le dossier Release/ (qui sont aux emplacements cités ci-dessus dans "Répertoires de bibliotheques supplémentaires")

