#include <SPI.h>
#include <SD.h>

File myFile;

void initializeCard(){//used to initialize our sd card very important to call it in the setup
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {//make sure to make your cs connected on pin 10 
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void writeInFile(char fileName[]){//send the file name to be written in as a parameter 
  myFile = SD.open(fileName, FILE_WRITE);Serial.println();
  if (myFile) {
    Serial.println("File is opened successfully \n");
    myFile.println("Here is test1 for writing in a file");//starting to wirte in file
    myFile.println("Hello World");
    myFile.close();//make sure to close the file after finishing
    Serial.println("Writing is finished & File is closed");
  } else {
    Serial.println("error opening the file");
  }
}

void readFromFile(char fileName[]){//send the file name to be read from as a parameter 
  myFile = SD.open(fileName);//default of second parameter of open func is read
  if (myFile) {
    Serial.println("File is opened successfully ");
    Serial.println("Reading from file in progress... ");Serial.println();
    while(myFile.available()){//while there is a data in the file read it and print it
      Serial.write(myFile.read());
      }
    myFile.close();//make sure to close the file after finishing
    Serial.println("Reading is finished & File is closed");
  } else {
    Serial.println("error opening the file or file isn't found");
  }
}

void createFile(char fileName[]){//send the file name to be created as a parameter 
  if(SD.exists(fileName)){//if the file already exists don't create it
    Serial.println("a file with that name is already created");
    return;
    }
  myFile=SD.open(fileName,FILE_WRITE);
  if(myFile){Serial.println("file is created successfully");}//if the file is successfully created & opened
  myFile.close();
}

void removeFile(char fileName[]){//send the file name to be removed as a parameter 
  if(!SD.exists(fileName)){//if file doesn't exists won't be able to remove it & return
    Serial.println("no file with that name exists to be removed");
    return;
    }
  SD.remove(fileName);
  if(!SD.exists(fileName)){Serial.println("file was successfully deleted");}
}

void printDirectory(File dir, int numTabs) {
  while (true) {//loop through all files in / dir
    File entry =  dir.openNextFile();
    if (! entry){//if no more files break
      break;
    }
    
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }

    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {//if it isn't a dir so print the file size
      Serial.print("  File_size=");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  initializeCard();
  removeFile("example.txt");
}

void loop() {
  // nothing happens after setup
}
