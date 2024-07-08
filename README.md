# geant4code

 
만약 geant4 코드가 어떻게 작동하는지 아직 모른다면 읽어주시길 바랍니다.

0. 전제조건

   본 코드는 현재 window의 ubuntu 환경에서 geant4 를 실행할 때를 기준으로 하고 있습니다.
   코드의 내용 자체는 linux OS 환경에서 사용해도 문제가 없습니다만 geant4를 실행 할 때 새 창마다 환경변수 설정이 요구됩니다.

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
   시각화 관련 해서는 /vis/ ( enable / disable ) 명령어를 통해 시각화를 활성화/비활성화 할 수 있습니다. 일반적으로 적은 이벤트 수에서는 켜 놓아도 무방하나 run 수가 많아질수록 시간이 시각화 작업으로 인해
   더 소요되게 되므로 이벤트 개수별로 임의 판단하에 설정합니다.

6. 로그 보는법 ( 프로세스 확인 )

   매크로의 verbose 옵션을 활성화 하게 되면 ( /tracking/verbose 1 로 설정 ) 터미널과 geant4 gui의 log window 에 tracking log 가 출력되게 됩니다.
   로그의 단위는 기본적으로 mm , MeV 이며 1번 옵션을 통해 활성화 한 경우 다음과 같은 정보들을 출력하게 됩니다.
   입자 종류, 입자의 trackID, parentID ( 모입자의 trackID ) , 각각 step의 정보 , x , y , z , 스텝간의 거리 , 총 이동거리 , 해당 스텝에서 입자의 운동에너지, 해당 스텝에서의 에너지 변화량 , 해당 스텝에서 당 입자
   가 상호작용한 프로세스 ( ex . brem , ionize, decay, capture , transport , etc. ) ( 최초 스텝은 상호작용 하지 않은 입자의 초기상태를 기술 하지만 물질에 overlap 해서 생성시킬 경우 최초 스텝부터 상호작용이 발    생 )

7. step numbering

   geant4 에서는 각각의 track 별 step을 구분하여 trackID 가 변화 할때마다 initialize 되는 기능이 별도로 존재하지 않습니다. ( stepping, tracking, event ) action.cc 에서 기록 할때부터 stepnumber를 initialize
   하는 옵션을 따로 설정해주거나 분석코드에서 변수를 따로 설정 후 조건에 따라 초기화 시키는 방법이 있습니다. 본 코드는 분석 코드에서 기전이 작동하도록 짜여 있습니다. ( action 에서 실행 할 경우 분석 코드를 실행 할
   때에는 매끄럽게 작동 하지만 코드 실행시 결과 데이터 도출까지의 시간이 약간 증가 할 수 있습니다. )

8. field 설정

   geant4에서는 코드를 통해 전기장과 자기장을 걸어 줄 수 있습니다. exampleB5 를 통해서 알 수 있지만 국소적 범위에 자기장을 걸어주거나 본 코드의 detectorconstruction 코드의 주석처리 된 부분처럼 world 전역에
   field 를 걸어줄 수 있습니다. 기전은 비슷하나 전기장과 자기장을 걸어주는 방식에 난이도 차이가 크기 때문에 field 를 걸어주는건 숙련이 된 후에 시도 하는 것이 좋습니다.



   ( 2024 - 07 - 03 , 강준혁 , christopher123@naver.com )

   
   
   
    
