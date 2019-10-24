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
  (let ((i 0)
	(j (vector-length lines)))
    (while (< i j)
      (printw x (+ i y) (vector-ref lines i))
      (set! i (+ i 1)))
    (refreshw)))

(define (draw-frames x y frames)
  (let ((x x)
	(i 0)
	(j (vector-length frames)))
    (while 1
      (clearw)
      (draw-lines x y (vector-ref frames i))
      (delayw sleep-ms)
      (set! x (+ x 1))
      (if (= i (- j 1))
	  (begin
	    (set! i 0)
	    (set! x (+ x 0)))
	  (set! i (+ i 1))))))
