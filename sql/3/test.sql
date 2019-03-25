--�������ݿ�
CREATE DATABASE db_Student
CREATE DATABASE cr32_student

--ɾ�����ݿ�
DROP DATABASE db_Student

DROP DATABASE cr32_student


--��
USE cr32_student

DROP TABLE tb_student

CREATE TABLE tb_student(
	stu_id INT PRIMARY KEY,
	stu_name VARCHAR(50)
	-- CONSTRAINT PRIMARY KEY(stu_id) -- ����Լ��
)

DROP TABLE tb_course

CREATE TABLE tb_course(
	course_id INT PRIMARY KEY,
	course_name VARCHAR(50)
	-- CONSTRAINT PRIMARY KEY(stu_id) -- ����Լ��
)

DROP TABLE tb_score

CREATE TABLE tb_score(
  stu_id INT,
	course_id INT,
	score INT,
	CONSTRAINT PRIMARY KEY(stu_id, course_id),
	FOREIGN KEY (stu_id) REFERENCES tb_student(stu_id),
  FOREIGN KEY (course_id) REFERENCES tb_course(course_id)	
)


ALTER TABLE tb_score
	DROP FOREIGN KEY tb_score_ibfk_2


INSERT INTO tb_course(course_id, course_name) VALUES(2, '��ѧ');
INSERT INTO tb_course(course_id, course_name) VALUES(3, 'Ӣ��')

-- AND
-- OR
-- NOT

DELETE FROM tb_course
			WHERE course_id > 1 AND course_id < 5

-- �޸�
UPDATE tb_score 
      SET score = 200
			WHERE stu_id = 1 AND course_id = 2;

