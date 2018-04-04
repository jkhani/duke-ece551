#include <fstream>

#include <iostream>

#include <string>

#include <dirent.h>

#include <unistd.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <map>


size_t hashFunc(std::string str){

  size_t res = 0;


  for (size_t i = 0;i < str.size();i++){

    res = res * 29 + (size_t)str[i];

  }

  return res;

}



void fileToHash(std::map<size_t, std::string> & fileMap, std::string dir){


  std::map<size_t, std::string>::iterator it;

  FILE * fin;

  DIR *dp = opendir(dir.c_str());

  struct dirent *dirp;

  struct stat fileStat;

  if (dp == NULL){

    return;

  }

  dirp = readdir(dp);

  while(dirp != NULL){

    if (std::string(dirp->d_name).compare(".") == 0 || std::string(dirp->d_name).compare("..") == 0) {

      dirp = readdir(dp);

      continue;

    }

    std::string filePath = dir + "/" + dirp->d_name;


    if (stat(filePath.c_str(), &fileStat)){

      dirp = readdir(dp);

      continue;

    }


    if (S_ISDIR(fileStat.st_mode))

      fileToHash(fileMap, filePath);


    else{

      std::string storage;

      int c;

      fin = fopen(filePath.c_str(),"r");

      if (fin == NULL){

	dirp = readdir(dp);

	continue;

      }

      while((c = fgetc(fin)) != EOF){

	storage.append(1,(char)c);

      }

      fclose(fin);

      it = fileMap.find(hashFunc(storage));

      if (it == fileMap.end()){

	fileMap[hashFunc(storage)] = filePath;

      }

      else{

	std::cout << "#Removing " << filePath << " (duplicate of " << it->second << ")." << std::endl;

	std::cout << "rm " << filePath << std::endl;

      }

    }


    dirp = readdir(dp);


  }


  closedir(dp);


  return;

}



int main(int argc, char ** argv){

  if (argc < 2){

    perror("Usage: dedup <files>\n");

    return EXIT_FAILURE;

  }


  std::cout << "#!/bin/bash" << std::endl;

  std::map<size_t, std::string> fileMap;


  for (int i = 1;i < argc;i++){

    std::string currentDir(argv[i]);

    fileToHash(fileMap, currentDir);

  }

  return EXIT_SUCCESS;



}
