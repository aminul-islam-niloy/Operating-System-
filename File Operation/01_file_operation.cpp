#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void createFile(string file_name) {
    fstream file;
    string name= file_name;

    file.open(file_name, ios::out);

    if (!file) {
        cout << "Error in creating file!!!" << endl;
    }
    else {
        cout << "File created successfully." << endl;
    }

    file.close();
}

void deleteFile(const string& filename) {
    if (remove(filename.c_str()) != 0) {
        cout << "Error in deleting file: " << filename << endl;
    }
    else {
        cout << "File deleted successfully: " << filename << endl;
    }
}

//  void copyFile(const string& source, const string& destination) {
//     ifstream sourceFile(source, ios::binary);
//     ofstream destFile(destination, ios::binary);

//     if (!sourceFile) {
//         cout << "Error in opening source file: " << source << endl;
//         return;
//     }

//     if (!destFile) {
//         cout << "Error in creating destination file: " << destination << endl;
//         sourceFile.close();
//         return;
//     }

//     destFile << sourceFile.rdbuf();

//     if (!destFile) {
//         cout << "Error in copying file: " << source << " to " << destination << endl;
//     }
//     else {
//         cout << "File copied successfully: " << source << " to " << destination << endl;
//     }

//     sourceFile.close();
//     destFile.close();
// }

void moveFile(const string& source, const string& destination) {
    if (rename(source.c_str(), destination.c_str()) != 0) {
        cout << "Error in moving file: " << source << " to " << destination << endl;
    }
    else {
        cout << "File moved successfully: " << source << " to " << destination << endl;
    }
}

void copyDirectory(const fs::path& sourceDir, const fs::path& destinationDir) {
    try {
        // Check if the source directory exists
        if (!fs::exists(sourceDir)) {
            std::cout << "Source directory does not exist: " << sourceDir << std::endl;
            return;
        }

        // Create the destination directory if it doesn't exist
        if (!fs::exists(destinationDir)) {
            fs::create_directories(destinationDir);
            std::cout << "Destination directory created: " << destinationDir << std::endl;
        }

        // Iterate through the source directory
        for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
            const fs::path& sourcePath = entry.path();
            const fs::path& relativePath = fs::relative(sourcePath, sourceDir);
            const fs::path& destinationPath = destinationDir / relativePath;

            if (fs::is_directory(sourcePath)) {
                // Create the corresponding directory in the destination
                fs::create_directories(destinationPath);
            } else {
                // Copy the file to the destination
                fs::copy_file(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
            }
        }

        std::cout << "Directory copied successfully: " << sourceDir << " to " << destinationDir << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error in copying directory: " << e.what() << std::endl;
    }
}

void createFolder(const string& folderName) {
    if (mkdir(folderName.c_str()) != 0) {
        cout << "Error in creating folder: " << folderName << endl;
    }
    else {
        cout << "Folder created successfully: " << folderName << endl;
    }
}

int main() {

while(true){
   int choice;
   cout<<endl;
   cout<<" ********************** ******************"<<endl;
   cout<<endl;
  cout << "Please choose an option:" << endl;
  cout << "1. Create file" << endl;
  cout << "2. Delete file" << endl;
  cout << "3. Copy file" << endl;
  cout << "4. Move file" << endl;
  
  cout<<endl;
  cout<<" ********************** ******************"<<endl;

  cout<<"Enter your choice : ";
  
  cin >> choice;
  
  string str_create,str_delete,str_source,str_desti;
  string str_dir_name,exi_dir,str_mov_f_name,target_dir_name;

  string source_path =  str_mov_f_name;
  string target_path = exi_dir + "/" + str_mov_f_name;
  string sourceDir, destinationDir;


  switch (choice) {
    case 1: 
          cout<<"Enter file name to create as like niloy.txt: ";
          cin>>str_create;
          createFile(str_create);
          break;

    case 2:
          cout<<"Enter file name to delete: ";
          cin>> str_delete;
          deleteFile(str_delete);
          break;

    case 3:      
            cout << "Enter the source directory path: ";
            getline(std::cin, sourceDir);
            cout << "Enter the destination directory path: ";
            getline(std::cin, destinationDir);

            copyDirectory(sourceDir, destinationDir);

          break;
    
    case 4:
        cout << "Do you want to create an folder? " << endl;
        cout<<" ********************** ******************"<<endl;
        cout << "1. Yes and create folder" << endl;
        cout << "2. No and move file" << endl;
        cout<<" ********************** ******************"<<endl;
        cout<<"Enter your choice: ";
        cin >> choice;
         
        switch (choice) {
            case 1: 
                cout<<"Enter folder name:  ";
                cin>>str_dir_name;
                createFolder(str_dir_name);
                break;

            case 2:
            cout<<"Select correct exesting folder to move file"<<endl;;
           
            
            cout<<"Enter dir and  source  file name: ";
            cin>>str_mov_f_name;
            // cout<<"Enter target file name:";
            // cin>>target_dir_name; 

             cout<<"Enter directory / filename name: ";
             cin>>exi_dir;    

            moveFile(str_mov_f_name,exi_dir);

            break;

    default:
      cout << "Invalid option." << endl;
      break;
        }
     
      break;
    default:
      cout << "Invalid option." << endl;
      break;
  }
}

    return 0;
}
