read -p $'Tem certeza bichao?\n'
if [[ "$REPLY" != "y" ]]; then
  echo $'Ih, vacilao'
  exit
fi
boca-submit-run user pass $1 c++11 $1.cpp

