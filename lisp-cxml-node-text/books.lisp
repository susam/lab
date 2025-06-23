(require "asdf")

(let ((*standard-output* (make-broadcast-stream)))
  (asdf:load-system "cxml"))

(defun get-node-text (node tag-name)
  (with-output-to-string (out)
    (let ((tag-nodes (dom:get-elements-by-tag-name node tag-name))
          (text))
      (when (plusp (dom:length tag-nodes))
        (let ((tag-node (dom:item tag-nodes 0)))
          (dom:do-node-list (tag-child-node (dom:child-nodes tag-node))
            (when (dom:text-node-p tag-child-node)
              (write-string (dom:data tag-child-node) out))))))))

(defun read-dom (doc)
  (dom:do-node-list (book (dom:get-elements-by-tag-name doc "book"))
    (format t "~%author: ~s~%" (get-node-text book "author"))
    (format t "title: ~s~%" (get-node-text book "title"))
    (format t "edition: ~s~%" (get-node-text book "edition"))
    (format t "year: ~s~%" (get-node-text book "year"))))

(read-dom (cxml:parse-file "books.xml" (cxml-dom:make-dom-builder)))

