(load-extension "./lib/libguile-ascii" "init_ascii")
(initw "./assets/FreeMono.ttf" 9 16)
(clearw)
(refreshw)

(define p #(#(" _N_  "
	      "<_===="
	      " |T|` "
	      " |||  ")
	    #(" _n_  "
	      "<_===="
	      "=/\\\\` "
	      "   \\\\ ")
	    #(" _N_  "
	      "<_===="
	      " |T|` "
	      " |||  ")
	    #(" _n_  "
	      "<_===="
	      "=//\\` "
	      "   \\\\ ")))

(define sleep-ms 150)

(define (draw-lines x y lines)  
  (do ((i 0 (+ i 1))
       (j (vector-length lines)))
      ((>= i j))
    (printw x (+ i y) (vector-ref lines i)))
  (refreshw))

(define (draw-frames x y frames)
  (let ((x x)
	(i 0)
	(j (vector-length frames)))
    (while 1
      (clearw)
      (draw-lines x y (vector-ref frames i))
      (delayw sleep-ms)
      (set! x (+ x 2))
      (if (= i (- j 1))
	  (begin
	    (set! i 0)
	    (set! x (+ x 0)))
	  (set! i (+ i 1))))))
