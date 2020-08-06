package ParseMenssages;
import java.sql.SQLException;

import ca.uhn.hl7v2.DefaultHapiContext;
import ca.uhn.hl7v2.HL7Exception;
import ca.uhn.hl7v2.HapiContext;
import ca.uhn.hl7v2.model.DataTypeException;
import ca.uhn.hl7v2.model.Message;
import ca.uhn.hl7v2.model.v23.datatype.TS;
import ca.uhn.hl7v2.model.v23.datatype.XAD;
import ca.uhn.hl7v2.model.v23.datatype.XPN;
import ca.uhn.hl7v2.model.v23.message.ADT_A04;
import ca.uhn.hl7v2.model.v23.segment.NK1;
import ca.uhn.hl7v2.model.v23.segment.PID;
import ca.uhn.hl7v2.parser.EncodingNotSupportedException;
import ca.uhn.hl7v2.parser.Parser;
    
public class Message_ADT_A04
{
  
      public static void main(String[] args) throws DataTypeException, InstantiationException, IllegalAccessException, ClassNotFoundException, SQLException {

    	  String msg = null;
    	  
    	  while (true) {
    		  /* Define which file containing an HL7 message should be parsed and read it */
    		  PostgreSQL database = new PostgreSQL("iCareWeb");
    		  database.connect();
    		  Long fileIndex = database.getFileIndex();
    		  Long id = database.getNextID();
    		  HandleFile read = new HandleFile(); 
    		  
    		  String filename = "msgs/in/ADT_A04_" + String.valueOf(fileIndex) + ".txt";
    		  
    		  if (read.testIfExist(filename) == true) {
    			  msg = read.readMsg(filename);
    			  database.incrementFileIndex(fileIndex);
    		  } else {
    			  break;
    		  }
    		     		    		  
    		  database.disconnect();

    		  /*
    		   * The HapiContext holds all configuration and provides factory methods for obtaining
    		   * all sorts of HAPI objects, e.g. parsers. 
    		   */
    		  HapiContext context = new DefaultHapiContext();

    		  /*
    		   * A Parser is used to convert between string representations of messages and instances of
    		   * HAPI's "Message" object. In this case, we are using a "GenericParser", which is able to
    		   * handle both XML and ER7 (pipe & hat) encodings.
    		   */
    		  Parser p = context.getGenericParser();

    		  Message hapiMsg;
    		  try {
    			  // The parse method performs the actual parsing
    			  hapiMsg = p.parse(msg);
    		  } catch (EncodingNotSupportedException e) {
    			  e.printStackTrace();
    			  return;
    		  } catch (HL7Exception e) {
    			  e.printStackTrace();
    			  return;
    		  }

    		  ADT_A04 adtMsg = (ADT_A04) hapiMsg;

    		  /* Segments */
    		  PID pid = adtMsg.getPID();
    		  NK1 nk1 = adtMsg.getNK1();

    		  /* PID information */       
    		  XPN patientName = pid.getPatientName(0);
    		  String familyName 	= patientName.getFamilyName().getValue();
    		  String givenName 	= patientName.getGivenName().toString();

    		  XAD patientAdress = pid.getPatientAddress(0);
    		  String street 	= patientAdress.getXad1_StreetAddress().getValue();
    		  String city 	= patientAdress.getXad3_City().getValue();
    		  String state 	= patientAdress.getXad4_StateOrProvince().getValue();
    		  String zip 	= patientAdress.getXad5_ZipOrPostalCode().getValue();
    		  //String country = patientAdress.getXad6_Country().getValue();
    		  //System.out.println(street + ", " + city + ", " + state + ", " + zip + ", " + country + ", " + otherDesignation + ", " + type);

    		  //String birthPlace = pid.getBirthPlace().getValue();
    		  //System.out.println("Birth Place: " + birthPlace); 

    		  TS dateOfBirth = pid.getDateOfBirth();
    		  int day 	= dateOfBirth.getTs1_TimeOfAnEvent().getDay();
    		  int month 	= dateOfBirth.getTs1_TimeOfAnEvent().getMonth();
    		  int year	= dateOfBirth.getTs1_TimeOfAnEvent().getYear();
    		  //System.out.println(day + "\\" + month + "\\" + year); 

    		  String sex				= pid.getSex().getValue();
    		  String motherGivenName	= pid.getMotherSMaidenName().getGivenName().getValue();
    		  String motherFamilyName	= pid.getMotherSMaidenName().getFamilyName().getValue();
    		  String email			= pid.getPhoneNumberHome(0).getXtn4_EmailAddress().getValue();
    		  String phoneNumber	 	= pid.getPhoneNumberHome(0).getXtn1_9999999X99999CAnyText().getValue();

    		  /* NK1 information */
    		  String parentGivenName = nk1.getNk12_NKName(0).getXpn2_GivenName().getValue();
    		  String parentFamilyName = nk1.getNk12_NKName(0).getXpn1_FamilyName().getValue();

    		  /* Database */
    		  database.connect();
    		  database.insert_ADT_A04_address(id, givenName, familyName, street, city, state, zip); 
    		  database.update_ADT_A04_dateOfBirth(id, day, month, year);
    		  database.update_ADT_A04_sex(id, sex);
    		  database.update_ADT_A04_motherName(id, motherGivenName, motherFamilyName);
    		  database.update_ADT_A04_responsable(id, parentGivenName, parentFamilyName);
    		  database.update_ADT_A04_email(id, email);
    		  database.update_ADT_A04_phoneNumber(id, phoneNumber);
    		  database.disconnect();
    	  }
      }
}
