(require "asdf")

(let ((*standard-output* (make-broadcast-stream)))
  (asdf:load-system "cxml"))

(defun esc (text)
  (when text
    (with-output-to-string (out)
      (loop for c across text do
        (write-char (if (char= c #\newline) (aref "↵" 0) c) out)))))

(defun walk-dom (node &optional (depth 0))
  (let ((indent (format nil "~v@{~a~:*~}" depth "  ")))
    (format t "~a<~a> ~a~:[~;~:* ~s~]~%" indent
            (dom:node-name node)
            (dom:node-type node)
            (esc (dom:node-value node)))
    (dom:do-node-list (child-node (dom:child-nodes node))
      (walk-dom child-node (1+ depth)))))

(walk-dom (cxml:parse-file "books.xml" (cxml-dom:make-dom-builder)))
