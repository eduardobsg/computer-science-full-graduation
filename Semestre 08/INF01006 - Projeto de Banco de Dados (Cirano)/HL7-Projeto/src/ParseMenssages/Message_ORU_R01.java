package ParseMenssages;

import java.io.IOException;
import java.sql.Timestamp;

import ca.uhn.hl7v2.HL7Exception;
import ca.uhn.hl7v2.model.Varies;
import ca.uhn.hl7v2.model.v25.datatype.CE;
import ca.uhn.hl7v2.model.v25.datatype.ST;
import ca.uhn.hl7v2.model.v25.datatype.TX;
import ca.uhn.hl7v2.model.v25.group.ORU_R01_OBSERVATION;
import ca.uhn.hl7v2.model.v25.group.ORU_R01_ORDER_OBSERVATION;
import ca.uhn.hl7v2.model.v25.message.ORU_R01;
import ca.uhn.hl7v2.model.v25.segment.OBR;
import ca.uhn.hl7v2.model.v25.segment.OBX;
    
public class Message_ORU_R01
{
  
	public static void main(String[] args) throws HL7Exception, IOException {

		PostgreSQL database = new PostgreSQL("iCareWeb");
		long[] results = null;
		
		long msgID = 0;
		long orderID = 0;
		Timestamp ts = new Timestamp(0);
		String desc = new String();
		
		int index = 1;
		
		while(true) {
			database.connect();
	    
			results = database.HL7msgsTable_selectData();
			
            if (results[0] == 0 && results[1] == 0) {
				System.out.println("Vazio");
				database.disconnect();
				break;
			}
			
            /* Message object is constructed */
            ORU_R01 message = new ORU_R01();
            
            /* Populate all mandatory MSH fields */
            message.initQuickstart("ORU", "R01", "T");

            /*
             * The OBR segment is contained within a group called ORDER_OBSERVATION, 
             * which is itself in a group called PATIENT_RESULT. These groups are
             * reached using named accessors.
             */
            ORU_R01_ORDER_OBSERVATION orderObservation = message.getPATIENT_RESULT().getORDER_OBSERVATION();
            
			msgID = database.getMsgID();
            orderID = database.getOrderID(msgID);
            ts = database.getTime(orderID);
			
            /* Populate the OBR */
            OBR obr = orderObservation.getOBR();
            obr.getSetIDOBR().setValue(String.valueOf(msgID));
            obr.getFillerOrderNumber().getEntityIdentifier().setValue(" ");
            obr.getFillerOrderNumber().getNamespaceID().setValue(" ");
            obr.getUniversalServiceIdentifier().getIdentifier().setValue(" ");
            obr.getObservationDateTime().getTime().setValue(ts);
            
            /*
             * The OBX segment is in a repeating group called OBSERVATION. You can 
             * use a named accessor which takes an index to access a specific 
             * repetition. You can ask for an index which is equal to the 
             * current number of repetitions,and a new repetition will be created.
             */
            ORU_R01_OBSERVATION observation = orderObservation.getOBSERVATION(0);
            
            /* Populate the first OBX */
            OBX obx = observation.getOBX();
            obx.getSetIDOBX().setValue("1");
            obx.getObservationIdentifier().getIdentifier().setValue("999999");
            obx.getObservationSubID().setValue("1");
            
            /* The first OBX has a value type of CE. So first, we populate OBX-2 with "CE"... */
            obx.getValueType().setValue("CE");
            
            /* ... then we create a CE instance to put in OBX-5. */
            CE ce = new CE(message);
            ce.getIdentifier().setValue(" ");
            ce.getText().setValue(" ");
            ce.getNameOfCodingSystem().setValue(" ");
            Varies value = obx.getObservationValue(0);
            value.setData(ce);
            
            /* Now we populate the second OBX */
            obx = orderObservation.getOBSERVATION(1).getOBX();
            obx.getSetIDOBX().setValue("2");
            obx.getObservationSubID().setValue("1");
            
            /* The second OBX in the sample message has an extra subcomponent at 
             * OBX-3-1. This component is actually an ST, but the HL7 specification allows
             * extra subcomponents to be tacked on to the end of a component. This is 
             * uncommon, but HAPI nontheless allows it.
             */
            ST observationIdentifier = obx.getObservationIdentifier().getIdentifier();
            observationIdentifier.setValue("999999");
            ST extraSubcomponent = new ST(message);
            extraSubcomponent.setValue("MDT");
            observationIdentifier.getExtraComponents().getComponent(0).setData(extraSubcomponent);
            
            /* The first OBX has a value type of TX. So first, we populate OBX-2 with "TX"... */
            obx.getValueType().setValue("TX");
                     
            /* ... then we create a CE instance to put in OBX-5. */
            desc = database.getDesc(orderID);
            TX tx = new TX(message);
            tx.setValue(desc);
            value = obx.getObservationValue(0);
            value.setData(tx);
             
            /* Print the message (remember, the MSH segment was not fully or correctly populated) */
            String msg = message.encode();
            System.out.println(msg);
            
            HandleFile handlefile = new HandleFile();
            handlefile.writeToFile(msg, "msgs/out/ORU_R01_" + index + ".txt");
            
            database.update_HL7msgsTable_status(results[0], false);
			database.disconnect();
			index++;
		}
		
		
	}
}
