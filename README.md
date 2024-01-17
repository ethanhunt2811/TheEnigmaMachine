## The Enigma Machine
The Enigma machine is a cipher device developed and used in the early- to mid-20th century to protect commercial, diplomatic, and military communication. It was employed extensively by Nazi Germany during World War II, in all branches of the German military. The Enigma machine was considered so secure that it was used to encipher the most top-secret messages.

The Enigma has an electromechanical rotor mechanism that scrambles the 26 letters of the alphabet. In typical use, one person enters text on the Enigma's keyboard and another person writes down which of the 26 lights above the keyboard illuminated at each key press. If plain text is entered, the illuminated letters are the ciphertext. Entering ciphertext transforms it back into readable plaintext. The rotor mechanism changes the electrical connections between the keys and the lights with each keypress.

The security of the system depends on machine settings that were generally changed daily, based on secret key lists distributed in advance, and on other settings that were changed for each message. The receiving station would have to know and use the exact settings employed by the transmitting station to successfully decrypt a message.


Cannot understand the description ?? <br />
Try running the enigma machine with <br />
Plugboard Configuration: <br />
A<-->L<br />
J<-->V<br />
Rotor Configuration:<br />
Rotor I: 1  Rotor II: 3  Rotor III: 4<br />
Reflector Configuration: UKW-A<br />
Ring Settings:<br />
Rotor I: A  Rotor II: A  Rotor III: H<br />
Rotor Offset:<br />
Rotor I: A  Rotor II: B  Rotor III: C<br />

## Steps to run

To execute just do make on the console, this will make binary file main and then simply execute main.

To make binaries manually, use below commands :-
```
    > g++ test.cpp enigma.cpp -o main
    > ./main
```
