(load-extension "./lib/libguile-ascii" "init_ascii")
(initw "./assets/FreeMono.ttf" 9 16)
(clearw)
(refreshw)

(define p #(#(" _N_  "
	      "<_===="
	      " |T|` "
	      " |||  ")
	    #(" _N_  "
	      "<_===="
	      "=/\\\\` "
	      "   \\\\ ")
	    #(" _N_  "
	      "<_===="
	      " |T|` "
	      " |||  ")
	    #(" _N_  "
	      "<_===="
	      "=//\\` "
	      "   \\\\ ")))

(define sleep-ms 150)

(define (draw-lines x y lines)
  (define i 0)
  (define l (vector-length lines))
  (while (< i l)
    (printw x (+ i y) (vector-ref lines i))
    (set! i (+ i 1)))
  (refreshw))

(define (draw-frames x y frames)
  (define cx x)
  (define i 0)
  (define l (vector-length frames))
  (while 1
    (clearw)
    (draw-lines cx y (vector-ref frames i))
    (delayw sleep-ms)
    (set! cx (+ cx 1))
    (if (= i (- l 1))
	(begin
	    (set! i 0)
	    (set! cx (+ cx 0)))
	(set! i (+ i 1)))))
