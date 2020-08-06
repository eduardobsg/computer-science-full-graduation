package ParseMenssages;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.logging.Level;
import java.util.logging.Logger;

public class PostgreSQL {

	String url = "jdbc:postgresql://localhost/";
    String user = "postgres";
    String password = "postgres";
    
    Connection con = null;
    PreparedStatement pst = null;
    ResultSet rs = null;
		
	/*
	 * Constructor - Just requires database.
	 */
	public PostgreSQL(String database) {
		this.url = this.url + database;
	}
	
	/*
	 * Constructor - Requires database, user and password.
	 */
	public PostgreSQL(String database, String user, String password) {
		this.url = this.url + database;
		this.user = user;
		this.password = password;
	}
	
	/*
	 * Connect 
	 */
	public void connect() {
		try {	
			this.con = null;  
			this.con = DriverManager.getConnection(this.url, this.user, this.password);
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
		}
	} 
	
	/*
	 * Disconnect 
	 */
	public void disconnect() {
		try {
			
			if (this.con != null) {
				this.con.close();
            }
			
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
		}
	}
	
	/*
	 * ADT_A04: Insert address
	 */
	public void insert_ADT_A04_address(long cdlpessoa, String givenName, String familyName,
			String street, String city, String state, String zip) {
        String stm = "INSERT INTO mbspessoa (cdlpessoa, nompessoa, loccidade, locestado, codcep, desendereco) "
           			+ "VALUES (?, ?, ?, ?, ?, ?)";
        
        try {
            this.pst = con.prepareStatement(stm);
            this.pst.setLong(1, cdlpessoa);
	        this.pst.setString(2, givenName + " " + familyName);
	        this.pst.setString(3, city);
	        this.pst.setString(4, state);
	        this.pst.setString(5, zip);
	        this.pst.setString(6, street);
	        this.pst.executeUpdate();
	        
	        if (this.pst != null) {
               	this.pst.close();
            }
	        
        } catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }	
	
        System.out.println(givenName + " " + familyName);
        System.out.println(street + ", " + city + ", " + state + ", " + zip);
	}
	
	/*
	 * ADT_A04: Update date of birth
	 */
	public void update_ADT_A04_dateOfBirth(long cdlpessoa, int day, int month, int year) {
		String date = "'" + Integer.toString(day) + "-" + Integer.toString(month) + "-" + Integer.toString(year) + "'";
		String stm = "UPDATE mbspessoa SET datfundnasc=" + date + " WHERE cdlpessoa=" + Long.toString(cdlpessoa);
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }	
		
		System.out.println(day + "/" + month + "/" + year);
	}
	
	/*
	 * ADT_A04: Update sex
	 */
	public void update_ADT_A04_sex(long cdlpessoa, String sex) {
		String stm = "UPDATE mbspessoa SET indsexo='" + sex + "' WHERE cdlpessoa=" + Long.toString(cdlpessoa);
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		System.out.println("Sex: " + sex);
	}
	
	/*
	 * ADT_A04: Update mother name
	 */
	public void update_ADT_A04_motherName(long cdlpessoa, String motherGivenName, String motherFamilyName) {
		String stm = "UPDATE mbspessoa SET nommae='" + motherGivenName + " " + motherFamilyName
				+ "' WHERE cdlpessoa=" + Long.toString(cdlpessoa);
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		System.out.println("Mother: " + motherGivenName + " " + motherFamilyName);
	}
	
	/*
	 * ADT_A04: Update relative responsable
	 */
	public void update_ADT_A04_responsable(long cdlpessoa, String parentGivenName, String parentFamilyName) {
		String stm = "UPDATE mbspessoa SET nomresponsavel='" + parentGivenName + " " + parentFamilyName
				+ "' WHERE cdlpessoa=" + Long.toString(cdlpessoa);
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		System.out.println(parentGivenName + " " + parentFamilyName);
	}
	
	/*
	 * ADT_A04: Update email
	 */
	public void update_ADT_A04_email(long cdlpessoa, String email) {
		String stm = "UPDATE mbspessoa SET codemail='" + email
				+ "' WHERE cdlpessoa=" + Long.toString(cdlpessoa);
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		System.out.println("Email: " + email);
	}
	
	/*
	 * ADT_A04: Update phone number
	 */
	public void update_ADT_A04_phoneNumber(long cdlpessoa, String phoneNumber) {
		String stm = "UPDATE mbspessoa SET destelefone1='" + phoneNumber
				+ "' WHERE cdlpessoa=" + Long.toString(cdlpessoa);
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
	}
	
	
	/*
	 * HL7msgs table: Select data
	 */
	public long[] HL7msgsTable_selectData() {		
		
		String stm = "SELECT * FROM hl7msgs WHERE status='true' LIMIT 1";
		
		long[] results = {0, 0};
		
		try {			
			this.pst = this.con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
				
            while (this.rs.next()) {
                results[0] = rs.getLong(1);
                results[1] = rs.getLong(2);
            }
            
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return results;
	}

	/*
	 * HL7msgs table: Update status
	 */
	public void update_HL7msgsTable_status(long cdlhl7msgs, boolean status) {
		String stm = "UPDATE hl7msgs SET status='" + status + "' WHERE cdlhl7msgs=" + cdlhl7msgs;
	
		try {
			this.pst = con.prepareStatement(stm);
			this.pst.executeUpdate();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
            Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
	}
	
	/*
	 * Get number for file from curretfileindex.
	 */
	public Long getFileIndex() {
		String stm = "SELECT currentindex FROM currentfileindex";
		Long val = (long)0;
		
		try {
			this.pst = con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
			
			this.rs.next();
			val = rs.getLong(1);
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return val;
	}
	
	/*
	 * Increment file index in table curretfileindex
	 */
	public void incrementFileIndex(Long fileIndex){
		Long val = fileIndex + 1;
		String stm = "UPDATE currentfileindex SET currentindex='" + val + "'";
		
		try {
			this.pst = con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
			
			if (this.pst != null) {
               	this.pst.close();
            }
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
			lgr.log(Level.SEVERE, ex.getMessage(), ex);
		}
	}
	
	/*
	 * Get next id for cdlpessoa field in mbspessoa table.
	 */
	public Long getNextID(){
		String stm = "SELECT MAX(cdlpessoa) FROM mbspessoa";
		Long val = (long)0;

		try {
			this.pst = con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
			this.rs.next();
			val = this.rs.getLong(1) + 1;
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return val;
	}
	
	
	/*
	 * Get hl7msgs id of the first ready.
	 */
	public Long getMsgID() {
		String stm = "SELECT cdlhl7msgs FROM hl7msgs WHERE status=true LIMIT 1";
		Long val = (long)0;

		try {
			this.pst = con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
			this.rs.next();
			val=this.rs.getLong(1);
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return val;
	}
	
	/*
	 * Get id of 'laudo'.
	 */
	public Long getOrderID(Long codMsg) {
		String stm = "SELECT cdllaudo FROM hl7msgs WHERE cdlhl7msgs='" + codMsg + "'";
		Long val = (long)0;

		try {
			this.pst = con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
			this.rs.next();
			val = this.rs.getLong(1);
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return val;
	}
	
	
	/*
	 * Get the time of the 'laudo'.
	 */
	public Timestamp getTime(Long id) {
		String stm = "SELECT datlaudo FROM tmedocorrencialaudo WHERE cdllaudo='" + id + "'";
		Timestamp ts = new Timestamp(0);

		try {
			this.pst = con.prepareStatement(stm);
			this.rs = this.pst.executeQuery();
			this.rs.next();
			ts = this.rs.getTimestamp(1);
		} catch (SQLException ex) {
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return ts;
	}
	
	/*
	 * Get the description of the laudo. 
	 */
	public String getDesc(Long id){
		String stm = "SELECT deslaudo FROM tmedocorrencialaudo WHERE cdllaudo='"+String.valueOf(id)+"';";
		String desc = new String();

		try{
		this.pst = con.prepareStatement(stm);
		this.rs = this.pst.executeQuery();
		this.rs.next();
		desc=this.rs.getString(1);
		
		
		
		} catch(SQLException ex){
			Logger lgr = Logger.getLogger(PostgreSQL.class.getName());
            lgr.log(Level.SEVERE, ex.getMessage(), ex);
        }
		
		return desc;
		
	}
	
}
