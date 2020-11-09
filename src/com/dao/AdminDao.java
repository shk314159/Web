package com.dao;

import com.model.DateCheck;
import com.model.Student;
import com.model.Teacher;
import com.model.admin;
import com.mysql.cj.conf.ConnectionUrlParser;
import javafx.util.Pair;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;

public class AdminDao extends BaseDao{
    private Connection conn = null;
    //管理员登录
    public int LoginAdmin(String Aid, String Apassword) { // 管理员登录
    //0:登录失败,0:普通教师，1：院级管理员,2:校级管理员,3:系统管理员
        try {
            System.out.println(Aid);
            System.out.println(Apassword);
            conn = dataSource.getConnection();
            String sqlStr = "SELECT Apassword, Arole FROM admin WHERE Aid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, Aid);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            if(rst.next()) {
//                System.out.println(1);
                System.out.println(rst.getString("Apassword"));
                if(rst.getString("Apassword").equals(Apassword)) {//判定是否登录成功
                    String Arole = rst.getNString("Arole");
                    System.out.println(Arole);
                    if(Arole.equals("院级管理员")) {
                        return 1;
                    }
                    else if(Arole.equals("校级管理员")) {
                        return 2;
                    }
                    else return 3;//系统管理员
                }
                else return 0;
            }
            else {
                return 0;
            }
        } catch (SQLException e1) {
            e1.printStackTrace();
            return 0;
        }
    }
    //管理员密码更改
    public boolean DeleteAdmin(String Aid) {
        try{
            conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            String sqlStr = "DELETE FROM admin WHERE Aid = " + Aid;
            System.out.println(sqlStr);
            st.executeUpdate(sqlStr);
            return true;
        } catch (SQLException e1) {
            System.out.println(e1);
            return false;
        }
    }

    public boolean ChangeAdminPassword(admin Admin) {
        try{
            conn =dataSource.getConnection();
            String sqlStr = "UPDATE admin SET Apassword = ? WHERE Aid = ?";
            System.out.println(sqlStr);
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, Admin.getAid());
            pstmt.setString(2, Admin.getApassword());
            pstmt.executeUpdate();
            return true;
        }catch (SQLException e1) {
            e1.printStackTrace();
            return false;
        }
    }
    //学生登录
    public Boolean LoginStudent(String Sid, String password) {
        try {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT Sidcard FROM student WHERE Sid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, Sid);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            if(rst.next()) { //Sid为唯一标识
                String Sidcard =  rst.getString("Sidcard");
                if(Sidcard.substring(Sidcard.length() - 8).equals(password)) {
                    return true;
                }
                else return false;
            }
            else {
                return false;
            }
        } catch (SQLException e1) {
            e1.printStackTrace();
            return false;
        }
    }
    //教师登录
    public boolean LoginTeacher(String Tid, String password) {
        try {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT Tidcard FROM teacher WHERE Tid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, Tid);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            if(rst.next()) { //Tid为唯一标识
                String Tidcard =  rst.getString("Tidcard");
                if(Tidcard.substring(Tidcard.length() - 8).equals(password)) {
                    return true;
                }
                else return false;
            }
            else {
                return false;
            }
        } catch (SQLException e1) {
            e1.printStackTrace();
            return false;
        }
    }
    //学生信息模糊查询
    public ArrayList<Student> findStudent(String Sid, String Sname, String Sidcard) {
        ArrayList<Student> StuList = new ArrayList<Student>();
        try  {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT * FROM teacher";
            if(Sid != null || Sname != null || Sidcard != null) {
                sqlStr += " WHERE ";
                if(Sid != null) {
                    sqlStr = sqlStr + "Sid like %" + Sid + "%";
                    if(Sname != null || Sidcard != null) {
                        sqlStr += " AND ";
                    }
                }
                if(Sname != null) {
                    sqlStr = sqlStr + "Sname like %" + Sname + "%";
                    if(Sidcard != null) {
                        sqlStr += " AND ";
                    }
                }
                if(Sidcard != null) {
                    sqlStr = sqlStr + "Sidcard like %" + Sidcard + "%";
                }
            }
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            while (rst.next()) {
                Student student = new Student();
                student.setSid(rst.getString("Sid"));
                student.setSname(rst.getString("Sname"));
                student.setSidcard(rst.getString("Sidcard"));
                student.setScollege(rst.getString("Scollege"));
                student.setSmajor(rst.getString("Smajor"));
                student.setSclass(rst.getString("Sclass"));
                student.setSdate(rst.getInt("Sdate"));
                student.setShealth(rst.getString("Shealth"));
                student.setStoday(rst.getInt("Stoday"));
                StuList.add(student);
            }
        } catch (SQLException se) {
            System.out.println(se);
            return null;
        }
        return StuList;
    }
    //教师信息模糊查询
    public ArrayList<Teacher> findTeacher(String Tid, String Tname, String Tidcard) {
        ArrayList<Teacher> TeaList = new ArrayList<Teacher>();
        try {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT * FROM teacher";
            if (Tid != null || Tname != null || Tidcard != null) {
                sqlStr += " WHERE ";
                if (Tid != null) {
                    sqlStr = sqlStr + "Tid like %" + Tid + "%";
                    if (Tname != null || Tidcard != null) {
                        sqlStr += " AND ";
                    }
                }
                if (Tname != null) {
                    sqlStr = sqlStr + "Tname like %" + Tname + "%";
                    if (Tidcard != null) {
                        sqlStr += " AND ";
                    }
                }
                if (Tidcard != null) {
                    sqlStr = sqlStr + "Tidcard like %" + Tidcard + "%";
                }
            }
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            while (rst.next()) {
                Teacher teacher = new Teacher();
                teacher.setTid(rst.getString("Tid"));
                teacher.setTname(rst.getString("Tname"));
                teacher.setTidcard(rst.getString("Tidcard"));
                teacher.setTcollege(rst.getString("Tcollege"));
                teacher.setTdate(rst.getInt("Tdate"));
                teacher.setThealth(rst.getString("Thealth"));
                teacher.setTtoday(rst.getInt("Ttoday"));
                TeaList.add(teacher);
            }
        }catch (SQLException se) {
            System.out.println(se);
            return null;
        }
        return TeaList;
    }
    //学生天数更新
    public Boolean UpdateDateStudent(String Sid, String nowhealth) {
        try {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT Sdate, Shealth FROM student WHERE Sid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, Sid);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            String Shealth = null;
            int Sdate = 0;
            if(rst.next()) { //Sid为唯一标识
                Shealth =  rst.getString("Shealth");
                Sdate = rst.getInt("Sdate");
                if("green".equals(nowhealth)) {
                    if("red".equals(Shealth) && Sdate == 6) {
                        Sdate = 0;
                        Shealth = "yellow";
                    }
                    else if("yellow".equals(Shealth) && Sdate == 6) {
                        Sdate = 0;
                        Shealth = "green";
                    }
                    else Sdate++;
                }
                else {
                    Sdate = 0;
                    if("green".equals(Shealth)) {
                        Shealth = nowhealth;
                    }
                    else if("yellow".equals(Shealth) && "red".equals(nowhealth)){
                        Shealth = "red";
                    }
                }
            }
            else {
                return false;
            }
            sqlStr = "UPDATE student SET Sdate = '"+Sdate+"', Shealth = '"+Shealth+"', Stoday='1' WHERE Sid = '"+Sid+"'";
            pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            pstmt.executeUpdate();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
            return false;
        }
    }
    //老师天数更新
    public Boolean UpdateDateTeacher(String Tid, String nowhealth) {
        try {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT Tdate, Thealth FROM teacher WHERE Tid = ?";
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, Tid);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            String Thealth = null;
            int Tdate = 0;
            if(rst.next()) { //Sid为唯一标识
                Thealth =  rst.getString("Thealth");
                Tdate = rst.getInt("Tdate");
                if("green".equals(nowhealth)) {
                    if("red".equals(Thealth) && Tdate == 6) {
                        Tdate = 0;
                        Thealth = "yellow";
                    }
                    else if("yellow".equals(Thealth) && Tdate == 6) {
                        Tdate = 0;
                        Thealth = "green";
                    }
                    else Tdate++;
                }
                else {
                    Tdate = 0;
                    if("green".equals(Thealth)) {
                        Thealth = nowhealth;
                    }
                    else if("yellow".equals(Thealth) && "red".equals(nowhealth)){
                        Thealth = "red";
                    }
                }
            }
            else {
                return false;
            }
            sqlStr = "UPDATE teacher SET Tdate = '"+Tdate+"', Thealth = '"+Thealth+"', Ttoday = 1 WHERE Tid = '"+Tid+"'";
            pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            pstmt.executeUpdate();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
            return false;
        }
    }
    //学生删除
    public Boolean DeleteStudent(String Sid) {
        try{
            conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            String sqlStr = "DELETE FROM student WHERE Sid = " + Sid;
            System.out.println(sqlStr);
            st.executeUpdate(sqlStr);
            return true;
        } catch (SQLException e1) {
            System.out.println(e1);
            return false;
        }
    }
    //教师删除
    public Boolean DeleteTeacher(String Tid) {
        try{
            conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            String sqlStr = "DELETE FROM teacher WHERE Tid = " + Tid;
            System.out.println(sqlStr);
            st.executeUpdate(sqlStr);
            return true;
        } catch (SQLException e1) {
            System.out.println(e1);
            return false;
        }
    }
    //学生信息修改
    public Boolean ModifyStudent(Student student) {
        String sqlStr = "UPDATE Student SET Sname = ?, Sgid = ?, Scollege = ?, Smajor = ?, Sclass = ?" +
                ",Shealth = ?, Sdate = ?, Stoday = ? WHERE Sid = ?";
        try {
            Connection conn = dataSource.getConnection();
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, student.getSname());
            pstmt.setString(2, student.getSidcard());
            pstmt.setString(3, student.getScollege());
            pstmt.setString(4, student.getSmajor());
            pstmt.setString(5, student.getSclass());
            pstmt.setString(6, student.getShealth());
            pstmt.setInt(7, student.getSdate());
            pstmt.setInt(8, student.getStoday());
            pstmt.setString(9, student.getSid());
            pstmt.executeUpdate();
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //教师信息修改
    public Boolean ModifyTeacher(Teacher teacher) {
        String sqlStr = "UPDATE Teacher SET Tname = ?, Tcollege = ?, Trole = ?," +
                " Thealth = ?, Tdate = ?, Ttoday = ? WHERE Tid = ?";
        try {
            Connection conn = dataSource.getConnection(); PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setString(1, teacher.getTname());
            pstmt.setString(2, teacher.getTcollege());
            pstmt.setString(3, teacher.getTrole());
            pstmt.setString(4, teacher.getThealth());
            pstmt.setInt(5, teacher.getTdate());
            pstmt.setInt(6, teacher.getTtoday());
            pstmt.setString(7, teacher.getTid());
            pstmt.executeUpdate();
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //学生单体添加
    public Boolean AddStudent(Student student) {
        String sqlStr = "INSERT INTO Student values('"+student.getSid()+"','"+student.getSname()+"','"+student.getSidcard()+
                "','"+student.getScollege()+"','"+student.getSmajor()+"','"+student.getSclass()+
                "', '"+student.getShealth()+"','"+student.getSdate()+"','"+student.getStoday()+"')";
        try {
            Connection conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            System.out.println(sqlStr);
            st.executeUpdate(sqlStr);
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //教师单体添加
    public Boolean AddTeacher(Teacher teacher) {
        String sqlStr = "INSERT INTO teacher values('"+teacher.getTid()+"','"+teacher.getTname()+"','"+teacher.getTidcard()+"','"+
                teacher.getTcollege()+"','"+teacher.getTrole()+"','"+teacher.getThealth()+"','"+teacher.getTdate()+"','"+teacher.getTtoday()+"')";
        try {
            Connection conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            st.executeUpdate(sqlStr);
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //学生群体添加
    public Boolean AddmoreStudent(ArrayList<Student> students) {
        String sqlStr = null;
        try {
            Connection conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            for(Student student : students) {
                sqlStr = "INSERT INTO Student values('"+student.getSid()+"','"+student.getSname()+"','"+student.getSidcard()+
                        "','"+student.getScollege()+"','"+student.getSmajor()+"','"+student.getSclass()+
                        "', '"+student.getShealth()+"','"+student.getSdate()+"','"+student.getStoday()+"')";
                st.executeUpdate(sqlStr);
            }
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //教师群体添加
    public Boolean AddmoreTeacher(ArrayList<Teacher> teachers) {
        String sqlStr = null;
        try {
            Connection conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            for(Teacher teacher : teachers) {
                sqlStr = "INSERT INTO teacher values('"+teacher.getTid()+"','"+teacher.getTname()+"','"+teacher.getTidcard()+"','"+
                        teacher.getTcollege()+"','"+teacher.getTrole()+"','"+teacher.getThealth()+"','"+teacher.getTdate()+"','"+teacher.getTtoday()+"')";
                st.executeUpdate(sqlStr);
            }
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //数据增加
    public Boolean AddData(DateCheck data) {
        String sqlStr = "INSERT INTO date values('"+data.getDate()+"','"+data.getTsum()+"','"+data.getTfinish()+
                "','"+data.getSsum()+"','"+data.getSfinish()+"','"+data.getTgreen()+
                "','"+data.getTyellow()+"','"+data.getTred()+"','"+data.getSgreen()+"','"+data.getSyellow()
                +"','"+data.getSred()+"')";
        try {
            Connection conn = dataSource.getConnection();
            Statement st = conn.createStatement();
            st.setMaxRows(20);
            System.out.println(sqlStr);
            st.executeUpdate(sqlStr);
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //数据更新
    public Boolean UpdateData(DateCheck data) {
        String sqlStr = "UPDATE data SET Tsum = ?, Tfinish = ?, Ssum = ?, Sfinish = ?" +
                ",Tred = ?, Tyellow = ?, Tgreen = ?, Sred = ?, Syellow = ?, Sgreen = ? WHERE Date = ?";
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
        try {
            Connection conn = dataSource.getConnection();
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            pstmt.setInt(1, data.getTsum());
            pstmt.setInt(2, data.getTfinish());
            pstmt.setInt(3, data.getSsum());
            pstmt.setInt(4, data.getSfinish());
            pstmt.setInt(5, data.getTred());
            pstmt.setInt(6, data.getTyellow());
            pstmt.setInt(7, data.getTgreen());
            pstmt.setInt(8, data.getSred());
            pstmt.setInt(9, data.getSyellow());
            pstmt.setInt(10, data.getSgreen());
            pstmt.setString(11, df.format(data.getDate()));
            pstmt.executeUpdate();
            return true;
        } catch (SQLException se) {
            se.printStackTrace();
            return false;
        }
    }
    //数据获取-打卡情况by日期
    public DateCheck GetDataByDate(Date date) {
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
        String dateStr = df.format(date);
        try {
            conn = dataSource.getConnection();
            String sqlStr = "SELECT * FROM data WHERE Date = '" +dateStr+"'";
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            if(rst.next()) {
                DateCheck data = new DateCheck();
                data.setDate(rst.getDate("Date"));
                data.setTsum(rst.getInt("Tsum"));
                data.setTfinish(rst.getInt("Tfinish"));
                data.setTgreen(rst.getInt("Tgreen"));
                data.setTyellow(rst.getInt("Tyellow"));
                data.setTred(rst.getInt("Tred"));
                data.setSsum(rst.getInt("Ssum"));
                data.setSfinish(rst.getInt("Sfinish"));
                data.setSgreen(rst.getInt("Sgreen"));
                data.setSyellow(rst.getInt("Syellow"));
                data.setSred(rst.getInt("Sred"));
                return data;
            }
            else {
                return null;
            }
        } catch (SQLException se) {
            System.out.println(se);
            return null;
        }
    }
    //数据获取-打卡情况by信息学生
    public Pair<DateCheck, ArrayList<Student>> GetDataOnStudent(String college, String major, String Class) {
        String sqlStr = "SELECT * FROM student";
        ArrayList<Student> StuList = new ArrayList<Student>();
        DateCheck dateCheck = null;
        if(college != null || major != null || Class != null) {
            sqlStr += " WHERE ";
            if(college != null) {
                sqlStr = sqlStr + "Scollege = " + college;
                if(major != null || Class != null) {
                    sqlStr += " AND ";
                }
            }
            if(major != null) {
                sqlStr = sqlStr + "Smajor = " + major;
                if(Class != null) {
                    sqlStr += " AND ";
                }
            }
            if(Class != null) {
                sqlStr = sqlStr + "Sclass = " + Class;
            }
        }
        try {
            conn = dataSource.getConnection();
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            int Ssum = 0;
            int Sfinish = 0;
            int Sred = 0;
            int Sgreen = 0;
            int Syellow = 0;
            while(rst.next()) {
                Ssum++;
                if(rst.getInt("Stoday") == 1) {
                    Sfinish++;
                }
                String judge = rst.getString("Shealth");
                if("green".equals(judge)) {
                    Sgreen++;
                }
                else if("red".equals(judge)) {
                    Sred++;
                }
                else Syellow++;
                Student student = new Student();
                student.setSid(rst.getString("Sid"));
                student.setSname(rst.getString("Sname"));
                student.setSidcard(rst.getString("Sidcard"));
                student.setScollege(rst.getString("Scollege"));
                student.setSmajor(rst.getString("Smajor"));
                student.setSclass(rst.getString("Sclass"));
                student.setSdate(rst.getInt("Sdate"));
                student.setShealth(rst.getString("Shealth"));
                student.setStoday(rst.getInt("Stoday"));
                StuList.add(student);
            }
            dateCheck.setSsum(Ssum);
            dateCheck.setSfinish(Sfinish);
            dateCheck.setSred(Sred);
            dateCheck.setSyellow(Syellow);
            dateCheck.setSgreen(Sgreen);
            Pair<DateCheck, ArrayList<Student>> data = new Pair<DateCheck, ArrayList<Student>>(dateCheck,StuList);
            conn
            return data;
        }catch (SQLException se) {
            System.out.println(se);
            return null;
        }
    }
    //数据获取-打卡情况by信息教师
    public Pair<DateCheck, ArrayList<Teacher>> GetDataOnTeacher(String college) {
        String sqlStr = "SELECT * FROM teacher";
        ArrayList<Teacher> TeaList = new ArrayList<Teacher>();
        DateCheck dateCheck = null;
        if(college != null) {
            sqlStr = sqlStr + " WHERE Tcollege = " + college;
        }
        try {
            PreparedStatement pstmt = conn.prepareStatement(sqlStr);
            System.out.println(sqlStr);
            ResultSet rst = pstmt.executeQuery();
            int Tsum = 0;
            int Tfinish = 0;
            int Tred = 0;
            int Tgreen = 0;
            int Tyellow = 0;
            while(rst.next()) {
                Tsum++;
                if(rst.getInt("Ttoday") == 1) {
                    Tfinish++;
                }
                String judge = rst.getString("Thealth");
                if("green".equals(judge)) {
                    Tgreen++;
                }
                else if("red".equals(judge)) {
                    Tred++;
                }
                else Tyellow++;
                Teacher teacher = new Teacher();
                teacher.setTid(rst.getString("Tid"));
                teacher.setTname(rst.getString("Tname"));
                teacher.setTidcard(rst.getString("Tidcard"));
                teacher.setTcollege(rst.getString("Tcollege"));
                teacher.setTdate(rst.getInt("Tdate"));
                teacher.setThealth(rst.getString("Thealth"));
                teacher.setTtoday(rst.getInt("Ttoday"));
                TeaList.add(teacher);
            }
            dateCheck.setTsum(Tsum);
            dateCheck.setTfinish(Tfinish);
            dateCheck.setTred(Tred);
            dateCheck.setTyellow(Tyellow);
            dateCheck.setTgreen(Tgreen);
            Pair<DateCheck, ArrayList<Teacher>> data = new Pair<DateCheck, ArrayList<Teacher>>(dateCheck,TeaList);
            return data;
        }catch (SQLException se) {
            System.out.println(se);
            return null;
        }
    }
}