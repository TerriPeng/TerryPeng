/*
    First name	Tianyi
    Last name		Peng
    Student ID	01382700 (e.g. 01234567)
    Username		tp17 (e.g. aaa123)
*/

//IMPORTANT: before submitting your source code, please make sure to comment your main function (needed for automated testing)


#include <iostream>
#include <string>
#include <map>
#include <vector> //or #include <list>

// do not use using namespace std

// do not alter the struct declaration
struct hufftreenode {
    char character;
    int frequency;
    hufftreenode* left;
    hufftreenode* right;
};

// do not alter the typedef
typedef hufftreenode* hufftreeptr;


// you can define and use any additional *structures* if you might need to

// YOUR CODE HERE FOR ADDIIONAL STRUCTS DECLARATION, IF ANY



/////////////////////////////////////////
// Functions declarations (prototypes) //
/////////////////////////////////////////

// do not alter these functions declarations

//utility function
bool valid_hufftree(const hufftreeptr hufftree);
 // returns true if the input hufftree is a valid Huffman tree
 // i.e. all the terminal nodes (leaves) have characters,
 // all the non-leaf nodes have two sub-trees each,
 // and the occurrence frequency of a non-leaf node equals
 // the sum of the occurrence frequencies of its two sub-trees.



std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable);
// encodes an input message (a string of characters) into an encoded message (string of bits) using the Huffman coding
// builds the Huffman tree and its associated encoding table (i.e. the association between the characters in the tree leaves and their encodings (string of bits))

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree);
// decodes an encoded message (a string of bits) into the original message (a string of characters) using the Huffman tree built during the encoding



// you can define and use any additional *functions* if you might need to

// YOUR CODE HERE FOR ADDIIONAL FUNCTIONS DECLARATION (NOT THE IMPLEMENTATION), IF ANY
void createhuffcode(const hufftreeptr& hufftree, std::string code, std::map<char, std::string>& hufftable);


///////////////////
// main function //
///////////////////

//IMPORTANT (Reminder): before submitting your source code, please make sure to comment your main function (needed for automated testing)
// int main() {
//
//     // YOUR CODE HERE FOR TESTING YOUR PROGRAM
//
//     // an example of basic encoding/decoding
//     std::string message, encodedmessage, decodedmessage;
//     hufftreeptr hufftree;
//     std::map<char, int> freqtable;
//     std::map<char, std::string> hufftable;
//
//     message = "go go gophers";
//
//     // 1) encoding (compression)
//
//     encodedmessage = huffencode(message, freqtable, hufftree, hufftable);
//
//     // freqtable should be as in Table 1.
//     // hufftree might be as in Figure 2 (remember, the Huffman coding tree IS NOT UNIQUE. If we swap two siblings in a Huffman tree, it is still a Huffman tree of the same message.)
//     // hufftable should correspond to hufftree, and might be as in Table 2 <' ',"100">, <'g',"00">, <'o',"01">, <'p',"1110">, <'h',"1101">, <'e',"101">, <'r',"1111">, <'s',"1100">.
//     // encodedmessage might then be the 37-bits string "0001100000110000011110110110111111100" (i.e. "00.01.100.00.01.100.00.01.1110.1101.101.1111.1100")
//     std::cout<<encodedmessage<<std::endl;
//
//     if(valid_hufftree(hufftree))  {
//         std::cout << "valid Huffman tree." << std::endl;
//     }
//     else {
//         std::cout << "not valid Huffman tree." << std::endl;
//     }
//
//     // // 2) decoding (uncompression)
//     decodedmessage = huffdecode(encodedmessage, hufftree);
//     // // should be "go go gophers"
//     std::cout<<decodedmessage<<std::endl;
//
//     if(decodedmessage == message) {
//         std::cout << "decoding OK." << std::endl;
//     }
//     else {
//         std::cout << "decoding not OK." << std::endl;
//     }
//
//     return 0;
// }


/////////////////////////////////////////////
// Functions definitions (implementations) //
/////////////////////////////////////////////

// YOUR CODE HERE FOR THE FUNCTIONS IMPLEMENTATIONS

std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable){

    std::string compressed = "\0";
    int count[256] = {0};
    std::map<char, int>::iterator it_freqtable;
    std::vector<hufftreeptr> forrest;
    std::map<char, std::string>::iterator it_hufftable;

    for(int i=0; i<message.length(); i++){
        count[message[i]]++;
    }//finding character frequencies

    for(int i = 0; i<256; i++){
        if(count[i]!=0){
            freqtable[char(i)] = count[i];
        }
    }//freqtable built

    for(it_freqtable = freqtable.begin(); it_freqtable!=freqtable.end(); it_freqtable++){
        hufftreeptr Tr = new hufftreenode;
        Tr->character = it_freqtable->first;
        Tr->frequency = it_freqtable->second;
        Tr->left = NULL;
        Tr->right = NULL;
        forrest.push_back(Tr);
    }//forrest created with single tree nodes

    while(forrest.size() > 1){
        hufftreeptr node = new hufftreenode;
        node->character = '\0';
        int min_freq = forrest[0]->frequency;
        hufftreeptr min_node;
        int save;
        for(int i = 0; i<forrest.size(); i++){
            if(min_freq >= forrest[i]->frequency){
                min_freq = forrest[i]->frequency;
                min_node = forrest[i];
                save = i;
            }
        }//for finding node with min frequency
        forrest.erase(forrest.begin()+save);
        node->left = min_node;
        node->frequency = min_node->frequency;

        min_freq = forrest[0]->frequency;
        for(int i = 0; i<forrest.size(); i++){
            if(min_freq >= forrest[i]->frequency){
            min_freq = forrest[i]->frequency;
            min_node = forrest[i];
            save = i;
            }
        }
        forrest.erase(forrest.begin()+save);
        node->right = min_node;
        node->frequency += min_node->frequency;
        forrest.push_back(node);
    }

    hufftree = forrest[0];

    createhuffcode(hufftree, compressed, hufftable);//function used to create hufftable

    for(int i=0; i<message.length(); i++){
        for(it_hufftable = hufftable.begin(); it_hufftable != hufftable.end(); it_hufftable++){
            if(message[i] == it_hufftable->first){
                compressed += it_hufftable->second;
            }
        }
    }//compressed code created
    return compressed;
}

void createhuffcode(const hufftreeptr& hufftree, std::string code, std::map<char, std::string>& hufftable){
    hufftreeptr tmp = hufftree;

    if(tmp->left == NULL && tmp->right == NULL){
        hufftable[tmp->character] = code;
    }

    if(tmp->left != NULL){
        createhuffcode(tmp->left, code + "0", hufftable);
    }

    if(tmp->right != NULL){
        createhuffcode(tmp->right, code + "1", hufftable);
    }
}

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree){
    hufftreeptr tmp = hufftree;
    std::string decoded;

    for(int i = 0; i<encodedmessage.length(); i++){
        if(encodedmessage[i] == '1'){
        tmp = tmp->right;
        }

        if(encodedmessage[i] == '0'){
        tmp = tmp->left;
        }

        if(tmp->left == NULL && tmp->right == NULL){
        decoded += tmp->character;
        tmp = hufftree;
        }
    }
    return decoded;
}

bool valid_hufftree(const hufftreeptr hufftree){
    hufftreeptr tmp = hufftree;
    while(tmp != NULL){
        if(tmp->left == NULL && tmp->right == NULL){
            if(tmp->character == '\0'){
                return false;
            }
        }//check if leaf nodes contain characters

        if((tmp->left != NULL && tmp->right == NULL)||(tmp->left == NULL && tmp->right != NULL)){
            return false;
        }//check if all non-leaf nodes have two sub trees

        if(tmp->left != NULL && tmp->right != NULL){
            if(tmp->frequency != (tmp->left->frequency + tmp->right->frequency)){
                return false;
            }
        }//check if all non-leaf nodes have frequency equal to the sum of its sub tree frequencies

        return valid_hufftree(tmp->left) & valid_hufftree(tmp->right);
    }
    return true;
}
