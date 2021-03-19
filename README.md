# CS120BLab14


eecs120b Lab 14 -Classic Pong


Lab‌ ‌14:‌ ‌Classic‌ ‌Pong‌ ‌
UCR‌ ‌EE/CS120B‌ ‌
 ‌
 
Description‌ ‌ ‌
 ‌ ‌
 
Create‌ ‌the‌ ‌classic‌ ‌pong‌ ‌game‌ ‌using‌ ‌the‌ ‌LED‌ ‌matrix.‌ ‌The‌ ‌classic‌ ‌LED‌ ‌pong‌ ‌game,‌ ‌if‌ ‌you‌ ‌
haven’t‌ ‌played,‌ ‌consists‌ ‌of‌ ‌a‌ ‌paddle‌ ‌on‌ ‌either‌ ‌side‌ ‌of‌ ‌the‌ ‌screen.‌ ‌A‌ ‌ball‌ ‌will‌ ‌bounce‌ ‌
between‌ ‌the‌ ‌paddles,‌ ‌and‌ ‌when‌ ‌it‌ ‌strikes‌ ‌a‌ ‌paddle‌ ‌it‌ ‌will‌ ‌bounce‌ ‌back‌ ‌towards‌ ‌the‌ ‌other‌ ‌
paddle.‌ ‌Depending‌ ‌on‌ ‌how‌ ‌it‌ ‌strikes‌ ‌the‌ ‌paddle‌ ‌it‌ ‌will‌ ‌bounce‌ ‌in‌ ‌a‌ ‌different‌ ‌manner.‌ ‌If‌ ‌the‌ ‌
paddle‌ ‌misses‌ ‌the‌ ‌ball,‌ ‌then‌ ‌the‌ ‌other‌ ‌player‌ ‌scores‌ ‌a‌ ‌point.‌ ‌ ‌
 ‌
 
The‌ ‌description‌ ‌of‌ ‌this‌ ‌project‌ ‌is‌ ‌intentionally‌ ‌open-ended‌ ‌compared‌ ‌to‌ ‌previous‌ ‌labs.‌ ‌
You‌ ‌are‌ ‌encouraged‌ ‌to‌ ‌think‌ ‌for‌ ‌yourself‌ ‌and‌ ‌be‌ ‌as‌ ‌creative‌ ‌as‌ ‌possible‌ ‌in‌ ‌terms‌ ‌of‌ ‌how‌ ‌
you‌ ‌implement‌ ‌the‌ ‌game.‌ ‌ ‌
 ‌ ‌
 
Required‌ ‌Components‌ ‌
 ‌ ‌
 
LED‌ ‌matrix,‌ ‌Shift‌ ‌Registers,‌ ‌Buttons,‌ ‌Keypad,‌ ‌and/or‌ ‌Joystick‌ ‌
 ‌ ‌
 
Basic‌ ‌requirements‌ ‌
 ‌ ‌
 
The‌ ‌classic‌ ‌pong‌ ‌game‌ ‌will‌ ‌be‌ ‌displayed‌ ‌on‌ ‌the‌ ‌LED‌ ‌matrix‌ ‌using‌ ‌shift‌ ‌registers‌ ‌to‌ ‌
control‌ ‌it.‌ ‌The‌ ‌player‌ ‌can‌ ‌control‌ ‌their‌ ‌paddle‌ ‌using‌ ‌multiple‌ ‌buttons,‌ ‌the‌ ‌keypad,‌ ‌or‌ ‌the‌ ‌
joystick‌ ‌--‌ ‌your‌ ‌choice!‌ ‌You‌ ‌will‌ ‌need‌ ‌a‌ ‌simple‌ ‌single‌ ‌player‌ ‌version‌ ‌of‌ ‌the‌ ‌game.‌ ‌The‌ ‌
other‌ ‌player‌ ‌will‌ ‌be‌ ‌controlled‌ ‌by‌ ‌a‌ ‌fairly‌ ‌basic‌ ‌AI‌ ‌engine.‌ ‌The‌ ‌AI‌ ‌will‌ ‌use‌ ‌a‌ ‌random‌ ‌
number‌ ‌to‌ ‌determine‌ ‌at‌ ‌each‌ ‌movement‌ ‌whether‌ ‌it‌ ‌follows‌ ‌the‌ ‌ball‌ ‌or‌ ‌not.‌ ‌You‌ ‌will‌ ‌need‌ ‌
to‌ ‌tweak‌ ‌the‌ ‌AI‌ ‌so‌ ‌that‌ ‌you‌ ‌are‌ ‌able‌ ‌to‌ ‌beat‌ ‌it‌ ‌sometimes.‌ ‌You‌ ‌may‌ ‌also‌ ‌create‌ ‌different‌ ‌
“difficulty”‌ ‌levels‌ ‌if‌ ‌you‌ ‌wish.‌ ‌The‌ ‌ball‌ ‌physics‌ ‌will‌ ‌be‌ ‌fairly‌ ‌simple.‌ ‌If‌ ‌the‌ ‌ball‌ ‌hits‌ ‌the‌ ‌
center‌ ‌of‌ ‌the‌ ‌paddle‌ ‌it‌ ‌will‌ ‌bounce‌ ‌off‌ ‌the‌ ‌paddle‌ ‌continuing‌ ‌along‌ ‌the‌ ‌same‌ ‌X‌ ‌direction‌ ‌it‌ ‌
was‌ ‌traveling‌ ‌in.‌ ‌If‌ ‌the‌ ‌ball‌ ‌hits‌ ‌the‌ ‌corner,‌ ‌then‌ ‌it‌ ‌will‌ ‌head‌ ‌in‌ ‌the‌ ‌opposite‌ ‌X‌ ‌direction.‌ ‌
You‌ ‌will‌ ‌also‌ ‌need‌ ‌a‌ ‌soft‌ ‌reset‌ ‌that‌ ‌will‌ ‌take‌ ‌you‌ ‌back‌ ‌to‌ ‌the‌ ‌intro‌ ‌when‌ ‌pressed.‌ ‌
 ‌ ‌
 ‌
 
 ‌
Advancement‌ ‌1‌ ‌
 ‌ ‌
 
Create‌ ‌a‌ ‌more‌ ‌complicated‌ ‌set‌ ‌of‌ ‌ball‌ ‌physics.‌ ‌This‌ ‌includes‌ ‌having‌ ‌the‌ ‌ball‌ ‌speed‌ ‌up‌ ‌
when‌ ‌it‌ ‌hits‌ ‌the‌ ‌corner‌ ‌of‌ ‌the‌ ‌paddle,‌ ‌as‌ ‌well‌ ‌as‌ ‌slowing‌ ‌down‌ ‌slightly‌ ‌when‌ ‌it‌ ‌hits‌ ‌the‌ ‌
center.‌ ‌You‌ ‌will‌ ‌also‌ ‌want‌ ‌the‌ ‌“spin”‌ ‌of‌ ‌the‌ ‌ball‌ ‌to‌ ‌change‌ ‌if‌ ‌the‌ ‌user‌ ‌moves‌ ‌the‌ ‌paddle‌ ‌
when‌ ‌it‌ ‌strikes‌ ‌the‌ ‌ball.‌ ‌This‌ ‌will‌ ‌affect‌ ‌how‌ ‌sharply‌ ‌the‌ ‌ball‌ ‌turns,‌ ‌and‌ ‌can‌ ‌also‌ ‌affect‌ ‌
speed.‌ ‌ ‌
  ‌ ‌
  
  
Advancement‌ ‌2‌ ‌
 ‌ ‌
 
Create‌ ‌a‌ ‌second‌ ‌player‌ ‌for‌ ‌the‌ ‌game;‌ ‌the‌ ‌second‌ ‌player‌ ‌should‌ ‌use‌ ‌a‌ ‌different‌ ‌control‌ ‌
mechanism‌ ‌than‌ ‌the‌ ‌first‌ ‌player‌ ‌(e.g.,‌ ‌if‌ ‌the‌ ‌first‌ ‌player‌ ‌uses‌ ‌buttons,‌ ‌then‌ ‌the‌ ‌second‌ ‌
player‌ ‌should‌ ‌use‌ ‌the‌ ‌joystick‌ ‌or‌ ‌keypad).‌ ‌You‌ ‌will‌ ‌be‌ ‌able‌ ‌to‌ ‌play‌ ‌against‌ ‌each‌ ‌other‌ ‌
and‌ ‌the‌ ‌winner‌ ‌is‌ ‌the‌ ‌one‌ ‌that‌ ‌wins‌ ‌the‌ ‌best‌ ‌3‌ ‌or‌ ‌5‌ ‌matches.‌ ‌You‌ ‌can‌ ‌change‌ ‌this‌ ‌
number‌ ‌if‌ ‌you‌ ‌would‌ ‌like,‌ ‌or‌ ‌make‌ ‌it‌ ‌an‌ ‌option‌ ‌for‌ ‌the‌ ‌users‌ ‌to‌ ‌select.‌ ‌Use‌ ‌LEDs‌ ‌to‌ ‌make‌ ‌
a‌ ‌simple‌ ‌menu‌ ‌and‌ ‌score‌ ‌keeper‌ ‌to‌ ‌allow‌ ‌either‌ ‌single-‌ ‌or‌ ‌multi-player‌ ‌gaming‌ ‌to‌ ‌be‌ ‌
selected,‌ ‌and‌ ‌to‌ ‌track‌ ‌the‌ ‌score‌ ‌during‌ ‌gameplay.‌ ‌ ‌
 ‌ ‌
 
 
Advancement‌ ‌3‌ ‌
 ‌ ‌
Implement‌ ‌a‌ ‌more‌ ‌sophisticated‌ ‌AI‌ ‌opponent‌ ‌for‌ ‌the‌ ‌single-player‌ ‌game‌ ‌
 ‌
 
 
