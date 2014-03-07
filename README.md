hangman
=======

A not so simple hangman game

## Features
1. Customizable hangman's body parts with **JSON**
2. Words stored in a **database**, easily extendable
3. **Multi-language** support

## Build and Run
**Pre-requisites**  
You need these libraries installed on your system in order to run the game:  
  1. **[SFML 2.1](http://sfml-dev.org/)**
  2. **[SQLite 3](http://www.sqlite.org/)**
  3. **[Kompex SQLite Wrapper](http://sqlitewrapper.kompex-online.com/)**

**Build**  
**1** - Download source code  
**2** - Extract it to a folder  
**3** - In a shell, go to the folder where you extracted the source code and run:  
```
$ make
```
**Run**  
**1** - Run the game:  
```
$ ./bin/hangman
```

## Customize hangman's body parts
In order to customize hangman's body parts you need to edit the JSON file located at: **./assets/json/default-body.json**, this file describes how hangman's body will be constructed.

1. **"texture"**: Texture file which contains the hangman's body part sprites. (Only one texture is allowed)  
The default texture which has been used to take the screenshots below looks like this:  
![alt tag](http://oi57.tinypic.com/200y04i.jpg)
2. **"bodypart"**: A hangman's body part
  1. **"order"**: The order of creation of the body part. A body part with order = 0 is needed because it will be the root node from which the other body parts will be created. The hangman's body parts are shown sorted by their order, starting at 0.
  2. **"txCoords"**: Coordinates of the texture file that contains that body part.
  3. **"joints"**: An array of joints.
    1. **"joint"**: Connection with another body part.
      1. **"order"**: Body part order to connect to.
      2. **"coords"**: Body part coordinates where to place the joint.
      3. **"h-align"**: Horizontal alignment of the joined body part.
      4. **"v-align"**: Vertical alignment of the joined body part.

The default hangman JSON looks like this:
```json
{
	"texture"  : "assets/images/hangman.png",
	"bodypart" :
	{
		"order"    : 0,
		"txCoords" : "0 0 28 28",
		"joints"   :
		{
			"joint" :
			{
				"order"   : 1,
				"coords"  : "14 28",
				"h-align" : "center",
				"v-align" : "top"
			}
		}
	},
	"bodypart" :
	{
		"order"    : 1,
		"txCoords" : "0 28 5 50",
		"joints"   :
		{
			"joint" :
			{
				"order"   : 2,
				"coords"  : "3 14",
				"h-align" : "right",
				"v-align" : "bottom"
			},
			"joint" :
			{
				"order"   : 3,
				"coords"  : "3 14",
				"h-align" : "left",
				"v-align" : "bottom"
			},
			"joint" :
			{
				"order"   : 4,
				"coords"  : "3 48",
				"h-align" : "right",
				"v-align" : "top"
			},
			"joint" :
			{
				"order"   : 5,
				"coords"  : "3 48",
				"h-align" : "left",
				"v-align" : "top"
			}
		}
	},
	"bodypart" :
	{
		"order"    : 2,
		"txCoords" : "6 28 30 19"
	},
	"bodypart" :
	{
		"order"    : 3,
		"txCoords" : "35 28 30 19"
	},
	"bodypart" :
	{
		"order"    : 4,
		"txCoords" : "6 47 30 19"
	},
	"bodypart" :
	{
		"order"    : 5,
		"txCoords" : "35 47 30 19"
	}
}
```

## Screenshots
