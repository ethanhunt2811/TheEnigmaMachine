#include "enigma.hpp"
#include <string>
#include <iostream>

//Constructor
enigma :: enigma() {
  resetPlugboard();
  rotor1 = 0;
  rotor2 = 1;
  rotor3 = 2;
  reflector = 0;
}

//Plugboard Configuration
void enigma :: resetPlugboard() {
  for(int i = 0; i < 26; i++) {
    plugboard[i] = i;
  }
}

void enigma :: displayPlugboardConfiguration() {
  cout << "Plugboard Configuration:\n";

  int count = 0;
  for(int i = 0; i < 26; i++) {
    if(plugboard[i] != i && plugboard[i] > i) {
      cout << char(i + 'A') << "<-->" << char(plugboard[i] + 'A') << "\n";
      count++;
    }
  }

  if(count == 0) {
    cout << "none\n";
  }
}

void enigma :: changePlugboardConfiguration() {
  resetPlugboard();

  char a = 'A', b = 'A';
  int count = -1;

  cout << "Enter Plugboard settings upto 10(Enter 0 0 to exit):\n";
  
  do {

    if(plugboard[a - 'A'] != (a - 'A') || plugboard[b - 'A'] != (b - 'A')) {
      cout << "Already connected to other letter\n";
    }
    else {
      plugboard[a - 'A'] = (b - 'A');
      plugboard[b - 'A'] = (a - 'A');
      count++;
      cout << ">> ";
    }

    if(count < 10) {
      cin >> a >> b;
    }

  } while( (a != '0' && b != '0') && count < 10 );
}

//rotor Configuration
void enigma :: displayRotorConfiguration() {
  cout << "Rotor Configuration:\nRotor I: " << rotor1 + 1 << "  Rotor II: " << rotor2 + 1 << "  Rotor III: " << rotor3 + 1 << "\n";
}

void enigma :: changeRotorConfiguration() {
  cout << "Select any 3 distinct rotors from 5:\n>> ";
  cin >> rotor1 >> rotor2 >> rotor3;
  if( (rotor1 > 5 || rotor2 > 5 || rotor3 > 5) || (rotor1 < 1 || rotor2 < 1 || rotor3 < 1) || (rotor1 == rotor2 || rotor2 == rotor3 || rotor1 == rotor3)) {
    cout << "Incorrect Rotors\n>> ";
    return changeRotorConfiguration();
  }
  else {
    rotor1 -= 1;
    rotor2 -= 1;
    rotor3 -= 1;
  }
}

//reflector Configuration
void enigma :: displayReflectorConfiguration() {
  cout << "Reflector Configuration: ";

  if(reflector == 0) {
    cout << "UKW-A\n";
  }
  else {
    cout << "UKW-B\n";
  }
}

void enigma :: changeReflectorConfiguration() {
  int choice = 0;
  
  cout << "Select Reflector Configuration :\n 1. UKW-A\n 2. UKW-B\n>> ";
  
  cin >> choice;

  if(choice == 1) {
    reflector = 0;
  }
  else if(choice == 2) {
    reflector = 1;
  }
  else {
    cout << "Enter correct option\n";
    changeReflectorConfiguration();
  }
}

//ring Configuration
void enigma :: displayRingConfiguration() {
  cout << "Ring Settings:" << "\nRotor I: " << char(ringSettings[rotor1] + 'A') << "  Rotor II: " << char(ringSettings[rotor2] + 'A') << "  Rotor III: " << char(ringSettings[rotor3] + 'A') << "\n";
}

void enigma :: changeRingConfiguration() {
  char rs1, rs2, rs3;

  cout << "Select Ring Settings for Rotor I, Rotor II and Rotor III respectively:\n>> ";
  cin >> rs1 >> rs2 >> rs3;
  
  if( (rs1 >= 'A' && rs1 <= 'Z') && (rs2 >= 'A' && rs2 <= 'Z') && (rs3 >= 'A' && rs3 <= 'Z')) {
    ringSettings[rotor1] = (rs1 - 'A');
    ringSettings[rotor2] = (rs2 - 'A');
    ringSettings[rotor3] = (rs3 - 'A');
  }
  else {
    cout << "Incorrect Ring Settings\n";
    return changeRingConfiguration();
  }
}

//rotor offset
void enigma :: displayRotorOffset() {
  cout << "Rotor Offset:" << "\nRotor I: " << char(rotorPosition[rotor1] + 'A') << "  Rotor II: " << char(rotorPosition[rotor2] + 'A') << "  Rotor III: " << char(rotorPosition[rotor3] + 'A') << "\n";
}

void enigma :: changeRotorOffset() {
  char ro1, ro2, ro3;

  cout << "Select Rotor Offset Configuration for Rotor I, Rotor II and Rotor III respectively:\n>> ";
  cin >> ro1 >> ro2 >> ro3;
  
  if( (ro1 >= 'A' && ro1 <= 'Z') && (ro2 >= 'A' && ro2 <= 'Z') && (ro3 >= 'A' && ro3 <= 'Z')) {
    rotorPosition[rotor1] = (ro1 - 'A');
    rotorPosition[rotor2] = (ro2 - 'A');
    rotorPosition[rotor3] = (ro3 - 'A');
  }
  else {
    cout << "Incorrect Rotor Offset Configuration\n";
    return changeRotorOffset();
  }
}

// Encrypt message
void enigma :: encrypt() {
  string inp, out;

  cout << "Enter Input message (Supported characters 'A'-'Z' and spaces):\n>> ";
  
  cin.ignore();
  getline(cin, inp);

  for(auto c : inp) {
    //Ignore Spaces
    if(c == ' ') {
      out += ' ';
      continue;
    }

    //Step Rotors
    bool stepRotor2 = false, stepRotor3 = false;
    if(rotorPosition[rotor1] == rotorsNotch[rotor1]) {
      stepRotor2 = true;
    } 
    if(rotorPosition[rotor2] == rotorsNotch[rotor2]) {
      stepRotor3 = true;
    }

    rotorPosition[rotor1] = (rotorPosition[rotor1] + 1) % 26;
    if(stepRotor2) {
      rotorPosition[rotor2] = (rotorPosition[rotor2] + 1) % 26;
    }
    if(stepRotor3) {
      rotorPosition[rotor3] = (rotorPosition[rotor3] + 1) % 26;
    }

    //Check Plugboard
    c = plugboard[c - 'A'] + 'A';

    //Rotor 1
    c = rotors[rotor1][ (ringSettings[rotor1] + rotorPosition[rotor1] + (c - 'A')) % 26] + 'A';

    //Rotor 2    
    c = rotors[rotor2][ (ringSettings[rotor2] + rotorPosition[rotor2] + (c - 'A')) % 26] + 'A';

    //Rotor 3
    c = rotors[rotor3][ (ringSettings[rotor3] + rotorPosition[rotor3] + (c - 'A')) % 26] + 'A';

    //Reflector
    c = reflectors[reflector][c - 'A'] + 'A';

    //Rotor 3 inverse    
    c = rotorsInv[rotor3][(c - 'A')] - (rotorPosition[rotor3] + ringSettings[rotor3]) % 26 < 0 ? 26 - ( (ringSettings[rotor3] + rotorPosition[rotor3]) % 26 - rotorsInv[rotor3][(c - 'A')] ) + 'A' : rotorsInv[rotor3][(c - 'A') % 26] - (rotorPosition[rotor3] + ringSettings[rotor3]) % 26 + 'A';

    //Rotor 2 Inverse
    c = rotorsInv[rotor2][(c - 'A')] - (rotorPosition[rotor2] + ringSettings[rotor2]) % 26 < 0 ? 26 - ( (ringSettings[rotor2] + rotorPosition[rotor2]) % 26 - rotorsInv[rotor2][(c - 'A')] ) + 'A' : rotorsInv[rotor2][(c - 'A') % 26] - (rotorPosition[rotor2] + ringSettings[rotor2]) % 26 + 'A';

    //Rotor 1 Inverse
    c = rotorsInv[rotor1][(c - 'A')] - (rotorPosition[rotor1] + ringSettings[rotor1]) % 26 < 0 ? 26 - ( (ringSettings[rotor1] + rotorPosition[rotor1]) % 26 - rotorsInv[rotor1][(c - 'A')] ) + 'A' : rotorsInv[rotor1][(c - 'A') % 26] - (rotorPosition[rotor1] + ringSettings[rotor1]) % 26 + 'A';

    //Check Plugboard
    c = plugboard[c - 'A'] + 'A';

    //Append Output
    out += c;
  }
  
  cout << "Encrypted Output >> " << out <<"\n";
}

void enigma :: menu() {

  char opt = 'x';
  do {
    cout << "------------------Configuration------------------\n";
    //plugboard Configuration
    displayPlugboardConfiguration();

    //rotor Configuration
    displayRotorConfiguration();

    //reflector Configuration
    displayReflectorConfiguration();

    //ring Configuration
    displayRingConfiguration();

    //rotor offset
    displayRotorOffset();

    //input
    cout << "-------------------------------------------------\n";
    cout << "Enter choice:\n  1. Change Plugboard Configuration\n  2. Change Rotor Configuration\n  3. Change Reflector Configuration\n  4. Change Ring Settings\n  5. Change Rotor Offset\n  6. Encrypt Message\n  x. Exit\n>> ";
    cin >> opt;

    switch(opt) {

      case '1' : {
        changePlugboardConfiguration();
        break;
      }

      case '2' : {
        changeRotorConfiguration();
        break;
      }

      case '3' : {
        changeReflectorConfiguration();
        break;
      }

      case '4' : {
        changeRingConfiguration();
        break;
      }

      case '5' : {
        changeRotorOffset();
        break;
      }

      case '6' : { 
        encrypt();
        break;
      }
      
      case 'x' : {
        break;
      }

      default  : {
        printf("Enter correct option");
      }
    }

  } while(opt != 'x');
}