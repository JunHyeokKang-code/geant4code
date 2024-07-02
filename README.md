# geant4code

 
만약 geant4 코드가 어떻게 작동하는지 아직 모른다면 읽어주시길 바랍니다.

1. step? event? track?
  geant4 에는 데이터를 저장하는 단위로 step, track, event 가 있습니다.
  우선 step은 interaction이나 어떤 happening이 일어난 한 순간을 기록한 것을 말합니다.
  각 순간 순간이 기록된다고 생각하면 되겠습니다.
  track 은 step이 모여서 이루는 하나의 trajectory인데 한개의 입자가 운동이 종료될때까지의 데이터를 말합니다
  모든 입자는 각각의 track을 가지고 있으며 trackID 를 할당 받지만 event가 다를 경우 trackid가 겹칠 수 있습니다.
  event 는 track들이 모여서 구성됩니다. 1개의 run을 실행 했을때 일어나는 모든 action의 데이터를 말하며
  같은 run 에서 발생한 모든 입자들 및 상호작용을 포괄합니다. 각각의 event는 1개의 eventID 를 공유합니다.

2. action.cc? action.hh?
   geant4 에서는 action.cc 파일을 통해 데이터 root파일의 형태를 통해 기록합니다. 각각의 파일들이 하는 역할은 다음과 같습니다.

   ****action.hh : cc 파일에서 사용할 함수를 정의하고 다른 파일들에서 해당 코드를 사용할 수 있게 import 할 수 있도록 하는 역할
   ****action.cc : 실제 코드가 돌아가는 파일. 해당 파일에서 해당 부분이 어떻게 작동하는지 설정할 수 있음.
    
   runaction : run 에 대한 데이터를 받도록 하는 코드. 어떤 데이터를 받을지 설정하여 해당 데이터를 받는 branch 를 열어줍니다.
   eventaction : event에 대한 데이터를 받도록 하는 코드. runaction 에서 설정한 데이터를 branch에 event 단위에서
                 받을 수 있는 데이터를 기록합니다
   trackingaction : track에 대한 데이터를 받도록 하는 코드. runaction 에서 설정한 데이터를 branch에 track 단위에서
                 받을 수 있는 데이터를 기록합니다
   steppingaction : step에 대한 데이터를 받도록 하는 코드. runaction 에서 설정한 데이터를 branch에 step 단위에서
                 받을 수 있는 데이터를 기록합니다.
   
   해당 파일들에서 받는 데이터가 한정되지는 않으나 일반적으로 이름을 통해 어떤 데이터를 주로 보려고 하는지 구분합니다.
   현재 작성된 코드는 step 위주로 다른 데이터를 포괄적으로 받습니다.
  
3. macro 파일 사용법
   코드를 살폈을때 build 파일 내에 vis.mac 파일이 있습니다. 해당 파일은 매크로 파일로 geant4 gui 에서 직접 입력할 명령어를 파일을 실행할때     바로 수행할 수 있도록 합니다.
   우선 확인 해야하는 명령어는 다음과 같습니다.
   verbose : 0 이면 로그 출력을 하지 않고 1 이면 로그를 터미널과 gui의 log window 에 출력합니다.
   visable : disable이면 본인이 구성한 detector를 시각화 하지 않고 enable이면 시각화하여 gui에 출력합니다.
   beamOn : 이 이후에 입력한 숫자만큼 입자를 발사합니다. 입자는 primarygeneratoraction 에서 작설정한 대로 발사됩니다.

4. 작동원리
   우선 physicslist에서 어떠한 물리법칙 상에서 움직이는지, 무시하는 process는 무엇이 있는지 설정합니다.
   그 후 detectorconstruction 에 작성된 대로 world 와 detector의 크기, 모양, 성분 등을 구성합니다.
   (안에 있는 시각화 옵션에서 색상 및 투명도 또한 조절 가능합니다.)
   다음에 primarygeneraotoraction 에서 설정된 대로 발사할 입자의 운동량, 에너지, 입자 종류가 설정되고
   매크로파일에 설정된 만큼 run을 발생 시키고 나서 action파일들이 operate 해서 데이터를 기록합니다.
   기록된 데이터는 각각의 branch에 저장되고 run이 종료된 후 .root 의 형태로 저장되게 됩니다.

5. 시각화 옵션
   gui에 시각화 된 경우 입자들의 trajectory가 시각화 되는데 전하에 따라 색상이 다르게 기록됩니다. 파란색은 + , 녹색은 중성, 빨간색은 - 전하를 나타냅니다. 
   
   
    
