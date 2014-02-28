CREATE TABLE "Categories" ("id" INTEGER PRIMARY KEY  NOT NULL ,"name" TEXT NOT NULL  DEFAULT (null) );
CREATE TABLE "CategoryWords" ("category_id" INTEGER NOT NULL , "word_id" INTEGER NOT NULL , PRIMARY KEY ("category_id", "word_id"));
CREATE TABLE "Dictionaries" ("id" INTEGER PRIMARY KEY  NOT NULL ,"name" TEXT NOT NULL  DEFAULT (null) ,"lang" TEXT NOT NULL  DEFAULT (null) ,"character_set" TEXT NOT NULL  DEFAULT (null) ,"font_file" TEXT NOT NULL  DEFAULT (null) );
CREATE TABLE "DictionaryCategories" ("dictionary_id" INTEGER NOT NULL , "category_id" INTEGER NOT NULL , PRIMARY KEY ("dictionary_id", "category_id"));
CREATE TABLE "Words" ("id" INTEGER PRIMARY KEY  NOT NULL ,"word" TEXT NOT NULL  DEFAULT (null) ,"hint" TEXT DEFAULT (null) );
