# Introduction

## Team members

Team 52: Joris

- Haoxuan Hong

- Chao Gu

- Yue Li

- Yuxiang He

- Enhua Fan

## Task allocation

In our team, everyone contributes to every part of the project, but there is a designated primary person responsible for each specific aspect.

1. Use cases:

    - primary: Yuxiang He
    - other team members

2. UML Class diagram:  
    - primary: Enhua Fan
    - other team members

3. UML Sequence diagrams:
    - primary: Enhua Fan
    - other team members

4. UML State machine diagrams:
    - primary: Haoxuan Hong
    - other team members

5. Implementation:
    - primary: Chao Gu
    - Session log: Enhua Fan
    - Time and date: Haoxuan Hong
    - PC part:  Yuxiang He
    - EEG part: Yue Li
    - Battery: Yue Li
    - New session: Chao Gu

6. Traceability matrix:
    - primary: Haoxuan Hong
    - other team members

## Set Env

1. Download the code from git

2. Copy the code into the OpenStack directory, placing it in the folder named `Team52`

3. Download the multimedia package

        sudo apt-get install qtmultimedia5-dev

4. Download `pulseaudio`

        sudo apt-get update
        sudo apt-get install pulseaudio

5. Create `.qrc` file

        cd /home/student/Downloads/
        vi beep.qrc

6. Copy fellow content into `beep.qrc` file

        <!DOCTYPE RCC>
        <RCC version="1.0">
        <qresource>
            <file>beep.wav</file>
        </qresource>
        </RCC>

7. Download the sound source

        wget https://www.soundjay.com/buttons/beep-01a.wav

8. Change name

        mv beep-01a.wav beep.wav

9. Use qt open the file Team.

## Set Git

1. choose one folder

        mkdir test
        cd test

2. download the git

        sudo apt-get install git

3. configure Git

        git config --global user.name "github name"
        git config --global user.email "email@example.com"

4. configure ssh

        ssh-keygen -t rsa -b 4096 -C "email@example.com"

    press enter to proceed

5. add the SSH Key

        eval "$(ssh-agent -s)"
        ssh-add ~/.ssh/id_rsa

6. install xclip

        sudo apt-get install xclip

7. copy the ssh into clipboard

        cat ~/.ssh/id_rsa.pub | xclip -sel clip

8. Add into GitHub account

    Go to GitHub, navigate to Settings > SSH and GPG keys > New SSH key, paste your key into the field, and save.

9. clone

        git clone git@github.com:YOURNAME/comp3004-team52.git

10. enter the folder

11. if you want to update

        git fetch origin