--
-- PostgreSQL database dump
--

-- Dumped from database version 9.2.4
-- Dumped by pg_dump version 9.2.4
-- Started on 2013-09-25 10:44:36

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;


--
-- TOC entry 242 (class 3079 OID 11727)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2534 (class 0 OID 0)
-- Dependencies: 242
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: -
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_with_oids = false;

--
-- TOC entry 168 (class 1259 OID 17409)
-- Name: admauditoria; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admauditoria (
    cdlauditoria bigint NOT NULL,
    codclasse character varying(255),
    codregistro character varying(255),
    datevento timestamp without time zone,
    codusuario character varying(255),
    desevento character varying(255),
    indtipoevento character varying(255)
);


--
-- TOC entry 169 (class 1259 OID 17415)
-- Name: admcustomer; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admcustomer (
    cdlcustomer bigint NOT NULL,
    cdlpessoa bigint,
    desadditionalinfo character varying(2000)
);


--
-- TOC entry 170 (class 1259 OID 17421)
-- Name: admdomain; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admdomain (
    cdidomain integer NOT NULL,
    desdomain character varying(2000),
    nomdomain character varying(255)
);


--
-- TOC entry 171 (class 1259 OID 17427)
-- Name: admempresa; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admempresa (
    cdlempresa bigint NOT NULL,
    cdlpessoa bigint
);


--
-- TOC entry 172 (class 1259 OID 17430)
-- Name: admgroup; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admgroup (
    codgroup character varying(16) NOT NULL,
    desgroup character varying(50) NOT NULL
);


--
-- TOC entry 173 (class 1259 OID 17433)
-- Name: admgroupmenuoption; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admgroupmenuoption (
    cdlmenuoption bigint NOT NULL,
    codgroup character varying(16) NOT NULL
);


--
-- TOC entry 174 (class 1259 OID 17436)
-- Name: admlocalatend; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admlocalatend (
    codlocal character varying(5) NOT NULL,
    cdlpessoa bigint,
    cdlcustomer bigint
);


--
-- TOC entry 175 (class 1259 OID 17439)
-- Name: admmenuoption; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admmenuoption (
    cdlmenuoption bigint NOT NULL,
    desmenuoption character varying(40) NOT NULL,
    nummenusequence integer NOT NULL,
    indtype integer,
    desparameters character varying(255),
    numconstantid integer,
    cdlparent bigint,
    codprogram character varying(40)
);


--
-- TOC entry 176 (class 1259 OID 17442)
-- Name: admparametro; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admparametro (
    nomparametro character varying(40) NOT NULL,
    desparam character varying(2000),
    valparam character varying(500)
);


--
-- TOC entry 177 (class 1259 OID 17448)
-- Name: admprogram; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admprogram (
    codprogram character varying(40) NOT NULL,
    desprogram character varying(50) NOT NULL,
    codfolder character varying(40)
);


--
-- TOC entry 178 (class 1259 OID 17451)
-- Name: admsequencia; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admsequencia (
    codsequencia character varying(50) NOT NULL,
    valsequencia numeric(38,0)
);


--
-- TOC entry 179 (class 1259 OID 17454)
-- Name: admusuario; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admusuario (
    codusuario character varying(255) NOT NULL,
    dessenha character varying(255),
    dessenhatemp character varying(50),
    indtype integer,
    indativo character varying(255),
    codlocal character varying(5),
    cdlpessoa bigint,
    cdlcustomer bigint,
    desclientversion character varying(255) DEFAULT ''::character varying
);


--
-- TOC entry 180 (class 1259 OID 17461)
-- Name: admusuariogroup; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admusuariogroup (
    codusuario character varying(255) NOT NULL,
    codgroup character varying(16) NOT NULL
);


--
-- TOC entry 181 (class 1259 OID 17464)
-- Name: admusuariotrust; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE admusuariotrust (
    cdlusuariotrust bigint NOT NULL,
    numtrust double precision,
    srcusuario character varying(255),
    dstusuario character varying(255)
);


--
-- TOC entry 182 (class 1259 OID 17470)
-- Name: geocity; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE geocity (
    idcity integer NOT NULL,
    codeibge integer,
    desname character varying(255),
    idstate integer
);


--
-- TOC entry 183 (class 1259 OID 17473)
-- Name: geocountry; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE geocountry (
    idcountry integer NOT NULL,
    desacronym character varying(2),
    desname character varying(255)
);


--
-- TOC entry 184 (class 1259 OID 17476)
-- Name: geostate; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE geostate (
    idstate integer NOT NULL,
    desacronym character varying(2),
    desname character varying(255),
    idcountry integer
);


--
-- TOC entry 185 (class 1259 OID 17479)
-- Name: gerapplication; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE gerapplication (
    codapplication character varying(255) NOT NULL,
    desname character varying(255),
    deslastversion character varying(255)
);


--
-- TOC entry 186 (class 1259 OID 17485)
-- Name: gerapplicationversion; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE gerapplicationversion (
    cdlversion bigint NOT NULL,
    datrelease timestamp without time zone,
    desversion character varying(255),
    desfilelocation character varying(255),
    deschangelog character varying(255),
    codapplication character varying(255)
);


--
-- TOC entry 239 (class 1259 OID 20153)
-- Name: homecaction; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE homecaction (
    idaction integer NOT NULL,
    desname character varying(255),
    indindex integer,
    desscript character varying(2000),
    idprotocol integer,
    indmandatory boolean
);


--
-- TOC entry 241 (class 1259 OID 20204)
-- Name: homecactiontreatment; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE homecactiontreatment (
    idactiontreatment integer NOT NULL,
    idprotocoltreatment integer,
    idaction integer,
    desobservations character varying(1000),
    datfinished timestamp without time zone,
    indfinished boolean
);


--
-- TOC entry 238 (class 1259 OID 20143)
-- Name: homecprotocol; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE homecprotocol (
    idprotocol integer NOT NULL,
    desname character varying(255),
    cdidomain integer
);


--
-- TOC entry 240 (class 1259 OID 20166)
-- Name: homecprotocoltreatment; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE homecprotocoltreatment (
    idprotocoltreatment integer NOT NULL,
    datfinished timestamp without time zone,
    indfinished boolean,
    desobservations character varying(1000),
    idprotocol integer,
    cdlpaciente bigint,
    cdlocorrencia bigint,
    codusuario character varying(255),
    cdlalert bigint,
    cdidomain integer
);


--
-- TOC entry 187 (class 1259 OID 17491)
-- Name: invcategory; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE invcategory (
    idcategory bigint NOT NULL,
    descategory character varying(255),
    desobservation character varying(2000)
);


--
-- TOC entry 188 (class 1259 OID 17497)
-- Name: invinstanceevent; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE invinstanceevent (
    idevent bigint NOT NULL,
    datevent timestamp without time zone,
    desobservation character varying(2000),
    indeventtype character varying(255),
    idassociation bigint,
    idinstance bigint
);


--
-- TOC entry 189 (class 1259 OID 17503)
-- Name: invinstancepatientassociation; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE invinstancepatientassociation (
    idassociation bigint NOT NULL,
    datfrom timestamp without time zone,
    datto timestamp without time zone,
    idinstance bigint,
    cdlpaciente bigint
);


--
-- TOC entry 190 (class 1259 OID 17506)
-- Name: invproduct; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE invproduct (
    idproduct bigint NOT NULL,
    desproduct character varying(255),
    indconsumable boolean,
    indidentifiertype character varying(255),
    nomproduct character varying(255),
    quantity integer,
    idcategory bigint
);


--
-- TOC entry 191 (class 1259 OID 17512)
-- Name: invproductinstance; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE invproductinstance (
    idinstance bigint NOT NULL,
    currentquantity integer,
    desinfo character varying(255),
    desobservation character varying(2000),
    indidentifier character varying(255),
    indstatus character varying(255),
    idproduct bigint
);


--
-- TOC entry 192 (class 1259 OID 17518)
-- Name: mbsethnicity; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbsethnicity (
    idethnicity bigint NOT NULL,
    codintegration character varying(255),
    desethnicity character varying(255)
);


--
-- TOC entry 193 (class 1259 OID 17524)
-- Name: mbsitem; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbsitem (
    coditem character varying(16) NOT NULL,
    indunidmedida character varying(2),
    desitem character varying(60),
    indprocedencia character varying(1),
    indtipo character varying(2)
);


--
-- TOC entry 194 (class 1259 OID 17527)
-- Name: mbsitemestrutura; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbsitemestrutura (
    cdnsequencia integer NOT NULL,
    valquantidade double precision,
    dtvalidadeini date,
    dtvalidadefim date,
    coditempai character varying(16) NOT NULL,
    coditemfilho character varying(16)
);


--
-- TOC entry 195 (class 1259 OID 17530)
-- Name: mbspessoa; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbspessoa (
    cdlpessoa bigint NOT NULL,
    loccidade character varying(255),
    datexpidentidade date,
    desobservacoes character varying(2000),
    destelefone2 character varying(17),
    destelefone1 character varying(17),
    codcnpjcpf character varying(255),
    nompessoa character varying(255),
    numversion integer,
    indescolar character varying(1),
    locestado character varying(255),
    complendereco character varying(255),
    indtipopessoa character varying(255),
    codcep character varying(9),
    codidentidade character varying(10),
    desendereco character varying(255),
    desimagedata bytea,
    locpais character varying(255),
    desestadocivil character varying(255),
    nompai character varying(255),
    desorgaoidentidade character varying(255),
    datfundnasc date,
    contatoresponsavel character varying(255),
    dessignature bytea,
    nommae character varying(255),
    nomresponsavel character varying(255),
    indsituacaocadastro character varying(255),
    locbairro character varying(255),
    indsexo character varying(1),
    codemail character varying(255),
    numendereco character varying(255),
    desprofissao character varying(255),
    cdidomain integer,
    relethnicity bigint,
    idcity integer,
    datcadastre timestamp without time zone,
    idcityplaceofbirth integer,
    idcountrynationality integer,
    datcadupdate timestamp without time zone,
    codusuariocad character varying(255),
    codusuarioupd character varying(255)
);


--
-- TOC entry 196 (class 1259 OID 17536)
-- Name: mbssmsmessage; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbssmsmessage (
    idmessage bigint NOT NULL,
    targetphonenumber character varying(50),
    messagebody character varying(255),
    status character varying(255),
    errormessage character varying(1000),
    cdidomain integer
);


--
-- TOC entry 237 (class 1259 OID 20033)
-- Name: mbssmstemplate; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbssmstemplate (
    idtemplate integer NOT NULL,
    desname character varying(255) NOT NULL,
    indactive boolean,
    phonenumbers character varying(1000),
    desmessagebody character varying(1000),
    cdidomain integer
);


--
-- TOC entry 197 (class 1259 OID 17542)
-- Name: mbsvideo; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbsvideo (
    cdlvideo bigint NOT NULL,
    desthumbnail bytea,
    desdescr character varying(2000),
    destitle character varying(255),
    desaddress character varying(255),
    indsource integer
);


--
-- TOC entry 198 (class 1259 OID 17548)
-- Name: mbsvideoprogram; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbsvideoprogram (
    codprogram character varying(20) NOT NULL,
    desprogram character varying(50)
);


--
-- TOC entry 199 (class 1259 OID 17551)
-- Name: mbsvideoprogramassoc; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbsvideoprogramassoc (
    cdlvideoprogramassoc bigint NOT NULL,
    numsequence integer,
    cdlvideo bigint,
    codprogram character varying(20)
);


--
-- TOC entry 200 (class 1259 OID 17554)
-- Name: mbswallcontribution; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbswallcontribution (
    cdlwallcontribution bigint NOT NULL,
    desname character varying(255),
    dessentence character varying(255),
    islocal boolean,
    contimestamp timestamp without time zone,
    cdlfather bigint,
    codusuario character varying(255)
);


--
-- TOC entry 201 (class 1259 OID 17560)
-- Name: mbswallcontributionassoc; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mbswallcontributionassoc (
    cdlwallcontribution bigint NOT NULL,
    codusuario character varying(255) NOT NULL
);


--
-- TOC entry 202 (class 1259 OID 17563)
-- Name: mrpplanning; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mrpplanning (
    codplanning character varying(10) NOT NULL,
    datplanning date NOT NULL,
    desplanning character varying(40) NOT NULL
);


--
-- TOC entry 203 (class 1259 OID 17566)
-- Name: mrpplanningitem; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE mrpplanningitem (
    cdnsequence integer NOT NULL,
    quantity integer,
    codplanning character varying(10) NOT NULL,
    coditem character varying(16)
);


--
-- TOC entry 204 (class 1259 OID 17569)
-- Name: tmedalert; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedalert (
    cdlalert bigint NOT NULL,
    datalert timestamp without time zone,
    indviewed boolean,
    cdlpaciente bigint,
    codrecording bigint,
    cdlocorrencia bigint
);


--
-- TOC entry 205 (class 1259 OID 17572)
-- Name: tmedalertvalue; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedalertvalue (
    cdlalertvalue bigint NOT NULL,
    desvalue character varying(255),
    desfield character varying(255),
    cdlalert bigint,
    indtype character varying(50),
    indcritical boolean,
    indcolor character varying(10),
    desintegrationcode character varying(255),
    numpriority integer
);


--
-- TOC entry 206 (class 1259 OID 17578)
-- Name: tmedbancofrase; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedbancofrase (
    cdlbancofrases bigint NOT NULL,
    indtype integer,
    cdlparent bigint,
    desdisplayname character varying(40),
    indprocesso character varying(255),
    numorder integer,
    destexttoinsert character varying(2000),
    cdlcustomer bigint
);


--
-- TOC entry 207 (class 1259 OID 17584)
-- Name: tmedbglrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedbglrecording (
    cdlrecording bigint NOT NULL,
    desdatedevice timestamp without time zone,
    indunit character varying(255),
    numbg integer,
    desdevicename character varying(255),
    coddeviceserial character varying(255),
    indmeasuretype integer DEFAULT 0,
    numvoltage double precision DEFAULT (-1)
);


--
-- TOC entry 208 (class 1259 OID 17592)
-- Name: tmedbprrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedbprrecording (
    cdlrecording bigint NOT NULL,
    valpresartdiast integer,
    valpulso integer,
    indunidade character varying(255),
    valpresartsist integer
);


--
-- TOC entry 209 (class 1259 OID 17595)
-- Name: tmeddevice; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmeddevice (
    cdldevice bigint NOT NULL,
    indtiposensor character varying(3),
    desfriendlyname character varying(255),
    indtipoconexao integer,
    desdevicename character varying(255),
    desaddress character varying(255),
    codusuario character varying(255)
);


--
-- TOC entry 210 (class 1259 OID 17601)
-- Name: tmeddicomrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmeddicomrecording (
    cdlrecording bigint NOT NULL,
    patientid character varying(255),
    seriestime character varying(255),
    studyid character varying(255),
    patientname character varying(255),
    imagetype character varying(255),
    studydate character varying(255),
    protocolname character varying(255),
    seriesdate character varying(255),
    seriesnumber character varying(255),
    studytime character varying(255),
    studyinstanceuid character varying(255),
    seriesdescription character varying(255),
    filename character varying(255),
    screenshotfilename character varying(255)
);


--
-- TOC entry 211 (class 1259 OID 17607)
-- Name: tmedecgrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedecgrecording (
    cdlrecording bigint NOT NULL,
    numintervalopq character varying(255),
    numduracaoqrs character varying(255),
    numganho integer,
    indeletrododesconectado character varying(255),
    desecgdata bytea,
    numeixop character varying(255),
    numintervaloqt character varying(255),
    numeixot character varying(255),
    numintervaloqtc character varying(255),
    numeixor character varying(255),
    numvelocidade integer,
    numultbatimentocard integer,
    numfrequencia integer,
    desfiltro character varying(255),
    numsensitividade double precision
);


--
-- TOC entry 212 (class 1259 OID 17613)
-- Name: tmedexam; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedexam (
    idexam bigint NOT NULL,
    codpriorityurgent character varying(255),
    codexam character varying(255),
    indactive boolean,
    desexam character varying(255),
    codpriorityroutine character varying(255),
    indexamtype character varying(255),
    cdlcustomer bigint
);


--
-- TOC entry 213 (class 1259 OID 17619)
-- Name: tmedimagerecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedimagerecording (
    cdlrecording bigint NOT NULL,
    indimagetype character varying(255),
    desimagedata bytea,
    codimageformat character varying(255),
    desimageref character varying(1000)
);


--
-- TOC entry 214 (class 1259 OID 17625)
-- Name: tmedmedico; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedmedico (
    cdlmedico bigint NOT NULL,
    cdipapel integer,
    codcrm character varying(255),
    descontato character varying(30),
    indativo character varying(255),
    cdlpessoa bigint,
    numversion integer DEFAULT 0
);


--
-- TOC entry 215 (class 1259 OID 17632)
-- Name: tmedmedicoesrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedmedicoesrecording (
    cdlrecording bigint NOT NULL,
    inddislipidemia boolean,
    valcperna numeric(5,2),
    indtabagista boolean,
    indinsufcardcong boolean,
    valglicose integer,
    valtemperatura numeric(3,1),
    valpresartdiast integer,
    valpresartsist integer,
    indasma boolean,
    valdctriceps numeric(3,1),
    valcbcontr numeric(5,2),
    indinfartoprevio boolean,
    indmarcapasso boolean,
    valfreqcardexe integer,
    valtriglicerid integer,
    valcolesterol integer,
    valdcsubescap numeric(3,1),
    valaltura numeric(3,2),
    valoximetria integer,
    valfreqresp integer,
    valdciliocr numeric(3,1),
    valnpassos integer,
    valhdlcolesterol integer,
    indhiparterial boolean,
    valccintura numeric(5,2),
    inddiabetesmelitus boolean,
    desmedicamentos character varying(2000),
    valcquadril numeric(5,2),
    valfreqcard integer,
    valdcabdom numeric(3,1),
    valcbrelax numeric(5,2),
    valdccoxa numeric(3,1),
    desoutrasinf character varying(2000),
    valpeso numeric(6,3),
    valldlcolesterol integer
);


--
-- TOC entry 216 (class 1259 OID 17638)
-- Name: tmedocorrencia; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedocorrencia (
    cdlocorrencia bigint NOT NULL,
    indprocesso character varying(5),
    deslocationlongitude character varying(255),
    datagendamento timestamp without time zone,
    indprioridade character varying(255),
    datexame timestamp without time zone,
    datvista timestamp without time zone,
    indestado character varying(255),
    desanotacoes character varying(2000),
    datexameservidor timestamp without time zone,
    deslocationlatitude character varying(255),
    desmotivoexame character varying(2000),
    codremoteid character varying(20),
    cdlmedicosolic bigint,
    codlocalmarcacao character varying(5),
    cdlfrase bigint,
    cdlpaciente bigint,
    codusuariosolic character varying(255),
    cdlpatientvet bigint,
    codlocalexame character varying(5),
    cdlcustomer bigint,
    codusuariolock character varying(255),
    codusuariovista character varying(255),
    idexam bigint,
    datlastmodification timestamp without time zone,
    desrequiredexam character varying(2000),
    datclosed character varying(255),
    codusuarioclosed character varying(255),
    indrejection integer DEFAULT 0,
    indbillable boolean DEFAULT true,
    desbillingreason character varying(2000),
    datcorrectedexam timestamp without time zone,
    indpublished boolean
);


--
-- TOC entry 217 (class 1259 OID 17646)
-- Name: tmedocorrencialaudo; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedocorrencialaudo (
    cdllaudo bigint NOT NULL,
    deslaudo character varying(4000),
    datlaudo timestamp without time zone,
    cdlocorrencia bigint,
    codusuariolaudo character varying(255)
);


--
-- TOC entry 218 (class 1259 OID 17652)
-- Name: tmedoxirecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedoxirecording (
    cdlrecording bigint NOT NULL,
    desoxidata bytea,
    numheartrate integer,
    numspo2 integer,
    numfrequencia integer
);


--
-- TOC entry 219 (class 1259 OID 17658)
-- Name: tmedpaciente; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpaciente (
    cdlpaciente bigint NOT NULL,
    indafdislipidemia boolean,
    indafdiabetes boolean,
    indafpneumopat boolean,
    desconvenio character varying(255),
    codcartaosus character varying(255),
    indafneuropat boolean,
    numversion integer,
    indconvenio boolean,
    indafcardiopat boolean,
    cdlpessoa bigint,
    codremoteid character varying(255),
    codremotesystem character varying(255),
    codcns character varying(15),
    codremoteid2 character varying(255)
);


--
-- TOC entry 220 (class 1259 OID 17664)
-- Name: tmedpatientdrugs; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientdrugs (
    cdlpacientedrugs bigint NOT NULL,
    desperiodofuse character varying(255),
    indusesanticoagulant boolean,
    indmorning boolean,
    indafternoon boolean,
    datstart timestamp without time zone,
    desactiveingredient character varying(255),
    indusespsychoactive boolean,
    indusesantidiabetic boolean,
    indwhenself boolean,
    desdrugname character varying(255),
    desdose character varying(255),
    desdailydose character varying(255),
    indnight boolean,
    datend timestamp without time zone,
    indwhenprescripted boolean,
    indwhensymptom boolean,
    cdlpatient bigint
);


--
-- TOC entry 221 (class 1259 OID 17670)
-- Name: tmedpatienthistoric; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatienthistoric (
    cdlhistoric bigint NOT NULL,
    desevento character varying(255),
    numanoevento integer,
    desobservation character varying(255),
    cdlpaciente bigint
);


--
-- TOC entry 222 (class 1259 OID 17676)
-- Name: tmedpatientprofile; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientprofile (
    cdlprofile integer NOT NULL,
    desname character varying(255),
    description character varying(255),
    cdlpatient bigint,
    cdidomain integer,
    numversion integer DEFAULT 0
);


--
-- TOC entry 223 (class 1259 OID 17683)
-- Name: tmedpatientprofileassociation; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientprofileassociation (
    cdlpatientprofileassociation bigint NOT NULL,
    cdlpaciente bigint,
    cdlprofile integer
);


--
-- TOC entry 224 (class 1259 OID 17686)
-- Name: tmedpatientprofilefield; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientprofilefield (
    cdlprofilefield integer NOT NULL,
    indusage integer,
    datlatestrequiredexam timestamp without time zone,
    numperiodicity integer,
    desfield character varying(255),
    codprogram character varying(20),
    cdlprofile integer,
    scheduletype character varying(255),
    weekdays character varying(255),
    missedexamintegrationcode character varying(255),
    nummissedexampriority integer
);


--
-- TOC entry 225 (class 1259 OID 17692)
-- Name: tmedpatientprofileschedule; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientprofileschedule (
    cdlschedule bigint NOT NULL,
    datnotifypatient character varying(5),
    numnotifyinterval integer,
    datschedulestart character varying(5),
    datnotifycenter character varying(5),
    cdlprofilefield integer
);


--
-- TOC entry 226 (class 1259 OID 17695)
-- Name: tmedpatientsupportnetwork; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientsupportnetwork (
    cdlpatientsupportnetwork bigint NOT NULL,
    indcontent boolean,
    descontact character varying(255),
    desname character varying(255),
    indsupportnettype integer,
    indkinship integer,
    desspecialization character varying(255),
    desobservation character varying(255),
    datbirthday timestamp without time zone,
    cdlpatient bigint
);


--
-- TOC entry 227 (class 1259 OID 17701)
-- Name: tmedpatientvet; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpatientvet (
    cdlpatientvet bigint NOT NULL,
    desfur character varying(255),
    desowner character varying(255),
    desname character varying(255),
    desbreed character varying(255),
    desspecies character varying(255),
    indsex character varying(1),
    datbirth date,
    cdlcustomer bigint
);


--
-- TOC entry 228 (class 1259 OID 17707)
-- Name: tmedpedrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedpedrecording (
    cdlrecording bigint NOT NULL,
    numsteps integer
);


--
-- TOC entry 229 (class 1259 OID 17710)
-- Name: tmedprofilefieldrange; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedprofilefieldrange (
    cdlfieldrange bigint NOT NULL,
    integrationcode character varying(255),
    lowerthreshold character varying(255),
    lowerlimit double precision,
    upperlimit double precision,
    generatealert boolean,
    color character varying(10),
    cdlprofilefield integer,
    idtemplate integer,
    idprotocol integer,
    numpriority integer
);


--
-- TOC entry 230 (class 1259 OID 17716)
-- Name: tmedprogramenrollment; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedprogramenrollment (
    cdlenrollment bigint NOT NULL,
    datdisenroll timestamp without time zone,
    datenroll timestamp without time zone,
    program character varying(255) NOT NULL,
    cdlpaciente bigint,
    patientgroup character varying(255),
    patienttype character varying(255)
);


--
-- TOC entry 231 (class 1259 OID 17722)
-- Name: tmedrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedrecording (
    cdlrecording bigint NOT NULL,
    indtiposensor character varying(3),
    desdate timestamp without time zone,
    desnomeeqpto character varying(255),
    cdlocorrencia bigint NOT NULL,
    idexam bigint,
    indpublished boolean,
    indstatus character varying(255),
    cdlrecordingsequel bigint
);


--
-- TOC entry 232 (class 1259 OID 17728)
-- Name: tmedsclrecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedsclrecording (
    cdlrecording bigint NOT NULL,
    weight numeric(6,3)
);


--
-- TOC entry 233 (class 1259 OID 17731)
-- Name: tmedvideorecording; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE tmedvideorecording (
    cdlrecording bigint NOT NULL,
    desvideoref character varying(1000)
);


--
-- TOC entry 234 (class 1259 OID 17737)
-- Name: vmeduser; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE vmeduser (
    coduser character varying(255) NOT NULL,
    despassword character varying(255),
    numuploadspeed integer,
    numsessionid bigint,
    numport integer,
    indmanualip boolean,
    desipaddress character varying(255),
    induserstatus integer,
    desusername character varying(255),
    datlastlogin timestamp without time zone
);


--
-- TOC entry 235 (class 1259 OID 17743)
-- Name: vmeduserconnection; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE vmeduserconnection (
    cdluserconnection bigint NOT NULL,
    datended timestamp without time zone,
    datlastkeepalive timestamp without time zone,
    indconnectionstatus integer,
    datstarted timestamp without time zone,
    codusersource character varying(255),
    codusertarget character varying(255)
);


--
-- TOC entry 236 (class 1259 OID 17749)
-- Name: vmeduserfriendship; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE vmeduserfriendship (
    cdluserfriendship bigint NOT NULL,
    codusersource character varying(255),
    codusertarget character varying(255)
);


--
-- TOC entry 2262 (class 2606 OID 17758)
-- Name: admauditoria_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admauditoria
    ADD CONSTRAINT admauditoria_pkey PRIMARY KEY (cdlauditoria);


--
-- TOC entry 2264 (class 2606 OID 17760)
-- Name: admcustomer_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admcustomer
    ADD CONSTRAINT admcustomer_pkey PRIMARY KEY (cdlcustomer);


--
-- TOC entry 2266 (class 2606 OID 17762)
-- Name: admdomain_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admdomain
    ADD CONSTRAINT admdomain_pkey PRIMARY KEY (cdidomain);


--
-- TOC entry 2268 (class 2606 OID 17764)
-- Name: admempresa_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admempresa
    ADD CONSTRAINT admempresa_pkey PRIMARY KEY (cdlempresa);


--
-- TOC entry 2270 (class 2606 OID 17766)
-- Name: admgroup_desgroup_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admgroup
    ADD CONSTRAINT admgroup_desgroup_key UNIQUE (desgroup);


--
-- TOC entry 2272 (class 2606 OID 17768)
-- Name: admgroup_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admgroup
    ADD CONSTRAINT admgroup_pkey PRIMARY KEY (codgroup);


--
-- TOC entry 2274 (class 2606 OID 17770)
-- Name: admgroupmenuoption_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admgroupmenuoption
    ADD CONSTRAINT admgroupmenuoption_pkey PRIMARY KEY (cdlmenuoption, codgroup);


--
-- TOC entry 2276 (class 2606 OID 17772)
-- Name: admlocalatend_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admlocalatend
    ADD CONSTRAINT admlocalatend_pkey PRIMARY KEY (codlocal);


--
-- TOC entry 2278 (class 2606 OID 17774)
-- Name: admmenuoption_numconstantid_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admmenuoption
    ADD CONSTRAINT admmenuoption_numconstantid_key UNIQUE (numconstantid);


--
-- TOC entry 2280 (class 2606 OID 17776)
-- Name: admmenuoption_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admmenuoption
    ADD CONSTRAINT admmenuoption_pkey PRIMARY KEY (cdlmenuoption);


--
-- TOC entry 2282 (class 2606 OID 17778)
-- Name: admparametro_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admparametro
    ADD CONSTRAINT admparametro_pkey PRIMARY KEY (nomparametro);


--
-- TOC entry 2284 (class 2606 OID 17780)
-- Name: admprogram_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admprogram
    ADD CONSTRAINT admprogram_pkey PRIMARY KEY (codprogram);


--
-- TOC entry 2286 (class 2606 OID 17782)
-- Name: admsequencia_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admsequencia
    ADD CONSTRAINT admsequencia_pkey PRIMARY KEY (codsequencia);


--
-- TOC entry 2288 (class 2606 OID 17784)
-- Name: admusuario_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuario
    ADD CONSTRAINT admusuario_pkey PRIMARY KEY (codusuario);


--
-- TOC entry 2290 (class 2606 OID 17786)
-- Name: admusuariogroup_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuariogroup
    ADD CONSTRAINT admusuariogroup_pkey PRIMARY KEY (codusuario, codgroup);


--
-- TOC entry 2292 (class 2606 OID 17788)
-- Name: admusuariotrust_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuariotrust
    ADD CONSTRAINT admusuariotrust_pkey PRIMARY KEY (cdlusuariotrust);


--
-- TOC entry 2294 (class 2606 OID 17790)
-- Name: geocity_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY geocity
    ADD CONSTRAINT geocity_pkey PRIMARY KEY (idcity);


--
-- TOC entry 2297 (class 2606 OID 17792)
-- Name: geocountry_desacronym_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY geocountry
    ADD CONSTRAINT geocountry_desacronym_key UNIQUE (desacronym);


--
-- TOC entry 2299 (class 2606 OID 17794)
-- Name: geocountry_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY geocountry
    ADD CONSTRAINT geocountry_pkey PRIMARY KEY (idcountry);


--
-- TOC entry 2301 (class 2606 OID 17796)
-- Name: geostate_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY geostate
    ADD CONSTRAINT geostate_pkey PRIMARY KEY (idstate);


--
-- TOC entry 2303 (class 2606 OID 17798)
-- Name: gerapplication_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY gerapplication
    ADD CONSTRAINT gerapplication_pkey PRIMARY KEY (codapplication);


--
-- TOC entry 2305 (class 2606 OID 17800)
-- Name: gerapplicationversion_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY gerapplicationversion
    ADD CONSTRAINT gerapplicationversion_pkey PRIMARY KEY (cdlversion);


--
-- TOC entry 2417 (class 2606 OID 20160)
-- Name: homecaction_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecaction
    ADD CONSTRAINT homecaction_pkey PRIMARY KEY (idaction);


--
-- TOC entry 2421 (class 2606 OID 20211)
-- Name: homecactiontreatment_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecactiontreatment
    ADD CONSTRAINT homecactiontreatment_pkey PRIMARY KEY (idactiontreatment);


--
-- TOC entry 2415 (class 2606 OID 20147)
-- Name: homecprotocol_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocol
    ADD CONSTRAINT homecprotocol_pkey PRIMARY KEY (idprotocol);


--
-- TOC entry 2419 (class 2606 OID 20173)
-- Name: homecprotocoltreatment_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT homecprotocoltreatment_pkey PRIMARY KEY (idprotocoltreatment);


--
-- TOC entry 2307 (class 2606 OID 17802)
-- Name: invcategory_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invcategory
    ADD CONSTRAINT invcategory_pkey PRIMARY KEY (idcategory);


--
-- TOC entry 2309 (class 2606 OID 17804)
-- Name: invinstanceevent_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invinstanceevent
    ADD CONSTRAINT invinstanceevent_pkey PRIMARY KEY (idevent);


--
-- TOC entry 2311 (class 2606 OID 17806)
-- Name: invinstancepatientassociation_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invinstancepatientassociation
    ADD CONSTRAINT invinstancepatientassociation_pkey PRIMARY KEY (idassociation);


--
-- TOC entry 2313 (class 2606 OID 17808)
-- Name: invproduct_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invproduct
    ADD CONSTRAINT invproduct_pkey PRIMARY KEY (idproduct);


--
-- TOC entry 2315 (class 2606 OID 17810)
-- Name: invproductinstance_indidentifier_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invproductinstance
    ADD CONSTRAINT invproductinstance_indidentifier_key UNIQUE (indidentifier);


--
-- TOC entry 2317 (class 2606 OID 17812)
-- Name: invproductinstance_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invproductinstance
    ADD CONSTRAINT invproductinstance_pkey PRIMARY KEY (idinstance);


--
-- TOC entry 2319 (class 2606 OID 17814)
-- Name: mbsethnicity_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsethnicity
    ADD CONSTRAINT mbsethnicity_pkey PRIMARY KEY (idethnicity);


--
-- TOC entry 2321 (class 2606 OID 17816)
-- Name: mbsitem_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsitem
    ADD CONSTRAINT mbsitem_pkey PRIMARY KEY (coditem);


--
-- TOC entry 2323 (class 2606 OID 17818)
-- Name: mbsitemestrutura_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsitemestrutura
    ADD CONSTRAINT mbsitemestrutura_pkey PRIMARY KEY (cdnsequencia, coditempai);


--
-- TOC entry 2325 (class 2606 OID 17820)
-- Name: mbspessoa_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbspessoa
    ADD CONSTRAINT mbspessoa_pkey PRIMARY KEY (cdlpessoa);


--
-- TOC entry 2327 (class 2606 OID 17822)
-- Name: mbssmsmessage_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbssmsmessage
    ADD CONSTRAINT mbssmsmessage_pkey PRIMARY KEY (idmessage);


--
-- TOC entry 2411 (class 2606 OID 20042)
-- Name: mbssmstemplate_desname_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbssmstemplate
    ADD CONSTRAINT mbssmstemplate_desname_key UNIQUE (desname);


--
-- TOC entry 2413 (class 2606 OID 20040)
-- Name: mbssmstemplate_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbssmstemplate
    ADD CONSTRAINT mbssmstemplate_pkey PRIMARY KEY (idtemplate);


--
-- TOC entry 2329 (class 2606 OID 17824)
-- Name: mbsvideo_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsvideo
    ADD CONSTRAINT mbsvideo_pkey PRIMARY KEY (cdlvideo);


--
-- TOC entry 2331 (class 2606 OID 17826)
-- Name: mbsvideoprogram_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsvideoprogram
    ADD CONSTRAINT mbsvideoprogram_pkey PRIMARY KEY (codprogram);


--
-- TOC entry 2333 (class 2606 OID 17828)
-- Name: mbsvideoprogramassoc_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsvideoprogramassoc
    ADD CONSTRAINT mbsvideoprogramassoc_pkey PRIMARY KEY (cdlvideoprogramassoc);


--
-- TOC entry 2335 (class 2606 OID 17830)
-- Name: mbswallcontribution_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbswallcontribution
    ADD CONSTRAINT mbswallcontribution_pkey PRIMARY KEY (cdlwallcontribution);


--
-- TOC entry 2337 (class 2606 OID 17832)
-- Name: mbswallcontributionassoc_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbswallcontributionassoc
    ADD CONSTRAINT mbswallcontributionassoc_pkey PRIMARY KEY (cdlwallcontribution, codusuario);


--
-- TOC entry 2339 (class 2606 OID 17834)
-- Name: mrpplanning_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mrpplanning
    ADD CONSTRAINT mrpplanning_pkey PRIMARY KEY (codplanning);


--
-- TOC entry 2341 (class 2606 OID 17836)
-- Name: mrpplanningitem_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mrpplanningitem
    ADD CONSTRAINT mrpplanningitem_pkey PRIMARY KEY (cdnsequence, codplanning);


--
-- TOC entry 2343 (class 2606 OID 17838)
-- Name: tmedalert_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedalert
    ADD CONSTRAINT tmedalert_pkey PRIMARY KEY (cdlalert);


--
-- TOC entry 2345 (class 2606 OID 17840)
-- Name: tmedalertvalue_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedalertvalue
    ADD CONSTRAINT tmedalertvalue_pkey PRIMARY KEY (cdlalertvalue);


--
-- TOC entry 2347 (class 2606 OID 17842)
-- Name: tmedbancofrase_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedbancofrase
    ADD CONSTRAINT tmedbancofrase_pkey PRIMARY KEY (cdlbancofrases);


--
-- TOC entry 2349 (class 2606 OID 17844)
-- Name: tmedbgrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedbglrecording
    ADD CONSTRAINT tmedbgrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2351 (class 2606 OID 17846)
-- Name: tmedbprrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedbprrecording
    ADD CONSTRAINT tmedbprrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2353 (class 2606 OID 17848)
-- Name: tmeddevice_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmeddevice
    ADD CONSTRAINT tmeddevice_pkey PRIMARY KEY (cdldevice);


--
-- TOC entry 2355 (class 2606 OID 17850)
-- Name: tmeddicomrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmeddicomrecording
    ADD CONSTRAINT tmeddicomrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2357 (class 2606 OID 17852)
-- Name: tmedecgrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedecgrecording
    ADD CONSTRAINT tmedecgrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2359 (class 2606 OID 17854)
-- Name: tmedexam_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedexam
    ADD CONSTRAINT tmedexam_pkey PRIMARY KEY (idexam);


--
-- TOC entry 2361 (class 2606 OID 17856)
-- Name: tmedimagerecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedimagerecording
    ADD CONSTRAINT tmedimagerecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2363 (class 2606 OID 17858)
-- Name: tmedmedico_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedmedico
    ADD CONSTRAINT tmedmedico_pkey PRIMARY KEY (cdlmedico);


--
-- TOC entry 2365 (class 2606 OID 17860)
-- Name: tmedmedicoesrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedmedicoesrecording
    ADD CONSTRAINT tmedmedicoesrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2367 (class 2606 OID 17862)
-- Name: tmedocorrencia_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT tmedocorrencia_pkey PRIMARY KEY (cdlocorrencia);


--
-- TOC entry 2369 (class 2606 OID 17864)
-- Name: tmedocorrencialaudo_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencialaudo
    ADD CONSTRAINT tmedocorrencialaudo_pkey PRIMARY KEY (cdllaudo);


--
-- TOC entry 2371 (class 2606 OID 17866)
-- Name: tmedoxirecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedoxirecording
    ADD CONSTRAINT tmedoxirecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2375 (class 2606 OID 17868)
-- Name: tmedpaciente_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpaciente
    ADD CONSTRAINT tmedpaciente_pkey PRIMARY KEY (cdlpaciente);


--
-- TOC entry 2377 (class 2606 OID 17870)
-- Name: tmedpatientdrugs_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientdrugs
    ADD CONSTRAINT tmedpatientdrugs_pkey PRIMARY KEY (cdlpacientedrugs);


--
-- TOC entry 2379 (class 2606 OID 17872)
-- Name: tmedpatienthistoric_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatienthistoric
    ADD CONSTRAINT tmedpatienthistoric_pkey PRIMARY KEY (cdlhistoric);


--
-- TOC entry 2381 (class 2606 OID 17874)
-- Name: tmedpatientprofile_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofile
    ADD CONSTRAINT tmedpatientprofile_pkey PRIMARY KEY (cdlprofile);


--
-- TOC entry 2383 (class 2606 OID 17876)
-- Name: tmedpatientprofileassociation_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofileassociation
    ADD CONSTRAINT tmedpatientprofileassociation_pkey PRIMARY KEY (cdlpatientprofileassociation);


--
-- TOC entry 2385 (class 2606 OID 17878)
-- Name: tmedpatientprofilefield_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofilefield
    ADD CONSTRAINT tmedpatientprofilefield_pkey PRIMARY KEY (cdlprofilefield);


--
-- TOC entry 2387 (class 2606 OID 17880)
-- Name: tmedpatientprofileschedule_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofileschedule
    ADD CONSTRAINT tmedpatientprofileschedule_pkey PRIMARY KEY (cdlschedule);


--
-- TOC entry 2389 (class 2606 OID 17882)
-- Name: tmedpatientsupportnetwork_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientsupportnetwork
    ADD CONSTRAINT tmedpatientsupportnetwork_pkey PRIMARY KEY (cdlpatientsupportnetwork);


--
-- TOC entry 2391 (class 2606 OID 17884)
-- Name: tmedpatientvet_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientvet
    ADD CONSTRAINT tmedpatientvet_pkey PRIMARY KEY (cdlpatientvet);


--
-- TOC entry 2393 (class 2606 OID 17886)
-- Name: tmedpedrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpedrecording
    ADD CONSTRAINT tmedpedrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2395 (class 2606 OID 17888)
-- Name: tmedprofilefieldrange_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedprofilefieldrange
    ADD CONSTRAINT tmedprofilefieldrange_pkey PRIMARY KEY (cdlfieldrange);


--
-- TOC entry 2397 (class 2606 OID 17890)
-- Name: tmedprogramenrollment_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedprogramenrollment
    ADD CONSTRAINT tmedprogramenrollment_pkey PRIMARY KEY (cdlenrollment);


--
-- TOC entry 2399 (class 2606 OID 17892)
-- Name: tmedrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedrecording
    ADD CONSTRAINT tmedrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2401 (class 2606 OID 17894)
-- Name: tmedsclrecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedsclrecording
    ADD CONSTRAINT tmedsclrecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2403 (class 2606 OID 17896)
-- Name: tmedvideorecording_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedvideorecording
    ADD CONSTRAINT tmedvideorecording_pkey PRIMARY KEY (cdlrecording);


--
-- TOC entry 2405 (class 2606 OID 17898)
-- Name: vmeduser_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduser
    ADD CONSTRAINT vmeduser_pkey PRIMARY KEY (coduser);


--
-- TOC entry 2407 (class 2606 OID 17900)
-- Name: vmeduserconnection_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduserconnection
    ADD CONSTRAINT vmeduserconnection_pkey PRIMARY KEY (cdluserconnection);


--
-- TOC entry 2409 (class 2606 OID 17902)
-- Name: vmeduserfriendship_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduserfriendship
    ADD CONSTRAINT vmeduserfriendship_pkey PRIMARY KEY (cdluserfriendship);


--
-- TOC entry 2295 (class 1259 OID 17903)
-- Name: idxidstate; Type: INDEX; Schema: public; Owner: -
--

CREATE INDEX idxidstate ON geocity USING btree (idstate);


--
-- TOC entry 2372 (class 1259 OID 17904)
-- Name: idxremoteid; Type: INDEX; Schema: public; Owner: -
--

CREATE INDEX idxremoteid ON tmedpaciente USING btree (codremoteid);


--
-- TOC entry 2373 (class 1259 OID 17905)
-- Name: idxremotesystem; Type: INDEX; Schema: public; Owner: -
--

CREATE INDEX idxremotesystem ON tmedpaciente USING btree (codremotesystem);


--
-- TOC entry 2527 (class 2606 OID 20212)
-- Name: fk_action_idprotocoltreatment; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecactiontreatment
    ADD CONSTRAINT fk_action_idprotocoltreatment FOREIGN KEY (idprotocoltreatment) REFERENCES homecprotocoltreatment(idprotocoltreatment);


--
-- TOC entry 2422 (class 2606 OID 17906)
-- Name: fk_admcustomer_cdlpessoa; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admcustomer
    ADD CONSTRAINT fk_admcustomer_cdlpessoa FOREIGN KEY (cdlpessoa) REFERENCES mbspessoa(cdlpessoa);


--
-- TOC entry 2423 (class 2606 OID 17911)
-- Name: fk_admempresa_cdlpessoa; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admempresa
    ADD CONSTRAINT fk_admempresa_cdlpessoa FOREIGN KEY (cdlpessoa) REFERENCES mbspessoa(cdlpessoa);


--
-- TOC entry 2424 (class 2606 OID 17916)
-- Name: fk_admgroupmenuoption_cdlmenuoption; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admgroupmenuoption
    ADD CONSTRAINT fk_admgroupmenuoption_cdlmenuoption FOREIGN KEY (cdlmenuoption) REFERENCES admmenuoption(cdlmenuoption);


--
-- TOC entry 2425 (class 2606 OID 17921)
-- Name: fk_admgroupmenuoption_codgroup; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admgroupmenuoption
    ADD CONSTRAINT fk_admgroupmenuoption_codgroup FOREIGN KEY (codgroup) REFERENCES admgroup(codgroup);


--
-- TOC entry 2426 (class 2606 OID 17926)
-- Name: fk_admlocalatend_cdlcustomer; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admlocalatend
    ADD CONSTRAINT fk_admlocalatend_cdlcustomer FOREIGN KEY (cdlcustomer) REFERENCES admcustomer(cdlcustomer);


--
-- TOC entry 2427 (class 2606 OID 17931)
-- Name: fk_admlocalatend_cdlpessoa; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admlocalatend
    ADD CONSTRAINT fk_admlocalatend_cdlpessoa FOREIGN KEY (cdlpessoa) REFERENCES mbspessoa(cdlpessoa);


--
-- TOC entry 2428 (class 2606 OID 17936)
-- Name: fk_admmenuoption_cdlparent; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admmenuoption
    ADD CONSTRAINT fk_admmenuoption_cdlparent FOREIGN KEY (cdlparent) REFERENCES admmenuoption(cdlmenuoption);


--
-- TOC entry 2429 (class 2606 OID 17941)
-- Name: fk_admmenuoption_codprogram; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admmenuoption
    ADD CONSTRAINT fk_admmenuoption_codprogram FOREIGN KEY (codprogram) REFERENCES admprogram(codprogram);


--
-- TOC entry 2430 (class 2606 OID 17946)
-- Name: fk_admusuario_cdlcustomer; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuario
    ADD CONSTRAINT fk_admusuario_cdlcustomer FOREIGN KEY (cdlcustomer) REFERENCES admcustomer(cdlcustomer);


--
-- TOC entry 2431 (class 2606 OID 17951)
-- Name: fk_admusuario_cdlpessoa; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuario
    ADD CONSTRAINT fk_admusuario_cdlpessoa FOREIGN KEY (cdlpessoa) REFERENCES mbspessoa(cdlpessoa);


--
-- TOC entry 2432 (class 2606 OID 17956)
-- Name: fk_admusuario_codlocal; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuario
    ADD CONSTRAINT fk_admusuario_codlocal FOREIGN KEY (codlocal) REFERENCES admlocalatend(codlocal);


--
-- TOC entry 2433 (class 2606 OID 17961)
-- Name: fk_admusuariogroup_codgroup; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuariogroup
    ADD CONSTRAINT fk_admusuariogroup_codgroup FOREIGN KEY (codgroup) REFERENCES admgroup(codgroup);


--
-- TOC entry 2434 (class 2606 OID 17966)
-- Name: fk_admusuariogroup_codusuario; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuariogroup
    ADD CONSTRAINT fk_admusuariogroup_codusuario FOREIGN KEY (codusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2435 (class 2606 OID 17971)
-- Name: fk_admusuariotrust_dstusuario; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuariotrust
    ADD CONSTRAINT fk_admusuariotrust_dstusuario FOREIGN KEY (dstusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2436 (class 2606 OID 17976)
-- Name: fk_admusuariotrust_srcusuario; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY admusuariotrust
    ADD CONSTRAINT fk_admusuariotrust_srcusuario FOREIGN KEY (srcusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2437 (class 2606 OID 17981)
-- Name: fk_geocity_idstate; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY geocity
    ADD CONSTRAINT fk_geocity_idstate FOREIGN KEY (idstate) REFERENCES geostate(idstate);


--
-- TOC entry 2438 (class 2606 OID 17986)
-- Name: fk_geostate_idcountry; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY geostate
    ADD CONSTRAINT fk_geostate_idcountry FOREIGN KEY (idcountry) REFERENCES geocountry(idcountry);


--
-- TOC entry 2439 (class 2606 OID 17991)
-- Name: fk_gerapplicationversion_codapplication; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY gerapplicationversion
    ADD CONSTRAINT fk_gerapplicationversion_codapplication FOREIGN KEY (codapplication) REFERENCES gerapplication(codapplication);


--
-- TOC entry 2526 (class 2606 OID 20217)
-- Name: fk_homecaction_idaction; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecactiontreatment
    ADD CONSTRAINT fk_homecaction_idaction FOREIGN KEY (idaction) REFERENCES homecaction(idaction);


--
-- TOC entry 2519 (class 2606 OID 20161)
-- Name: fk_homecaction_idprotocol; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecaction
    ADD CONSTRAINT fk_homecaction_idprotocol FOREIGN KEY (idprotocol) REFERENCES homecprotocol(idprotocol);


--
-- TOC entry 2518 (class 2606 OID 20148)
-- Name: fk_homecprotocol_cdidomain; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocol
    ADD CONSTRAINT fk_homecprotocol_cdidomain FOREIGN KEY (cdidomain) REFERENCES admdomain(cdidomain);


--
-- TOC entry 2520 (class 2606 OID 20199)
-- Name: fk_hptreatment_cdidomain; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT fk_hptreatment_cdidomain FOREIGN KEY (cdidomain) REFERENCES admdomain(cdidomain);


--
-- TOC entry 2521 (class 2606 OID 20194)
-- Name: fk_hptreatment_cdlalert; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT fk_hptreatment_cdlalert FOREIGN KEY (cdlalert) REFERENCES tmedalert(cdlalert);


--
-- TOC entry 2523 (class 2606 OID 20184)
-- Name: fk_hptreatment_cdlocorrencia; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT fk_hptreatment_cdlocorrencia FOREIGN KEY (cdlocorrencia) REFERENCES tmedocorrencia(cdlocorrencia);


--
-- TOC entry 2524 (class 2606 OID 20179)
-- Name: fk_hptreatment_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT fk_hptreatment_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2522 (class 2606 OID 20189)
-- Name: fk_hptreatment_coduser; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT fk_hptreatment_coduser FOREIGN KEY (codusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2525 (class 2606 OID 20174)
-- Name: fk_hptreatment_idprotocol; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY homecprotocoltreatment
    ADD CONSTRAINT fk_hptreatment_idprotocol FOREIGN KEY (idprotocol) REFERENCES homecprotocol(idprotocol);


--
-- TOC entry 2440 (class 2606 OID 17996)
-- Name: fk_invinstanceevent_idassociation; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invinstanceevent
    ADD CONSTRAINT fk_invinstanceevent_idassociation FOREIGN KEY (idassociation) REFERENCES invinstancepatientassociation(idassociation);


--
-- TOC entry 2441 (class 2606 OID 18001)
-- Name: fk_invinstanceevent_idinstance; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invinstanceevent
    ADD CONSTRAINT fk_invinstanceevent_idinstance FOREIGN KEY (idinstance) REFERENCES invproductinstance(idinstance);


--
-- TOC entry 2442 (class 2606 OID 18006)
-- Name: fk_invinstancepatientassociation_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invinstancepatientassociation
    ADD CONSTRAINT fk_invinstancepatientassociation_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2443 (class 2606 OID 18011)
-- Name: fk_invinstancepatientassociation_idinstance; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invinstancepatientassociation
    ADD CONSTRAINT fk_invinstancepatientassociation_idinstance FOREIGN KEY (idinstance) REFERENCES invproductinstance(idinstance);


--
-- TOC entry 2444 (class 2606 OID 18016)
-- Name: fk_invproduct_idcategory; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invproduct
    ADD CONSTRAINT fk_invproduct_idcategory FOREIGN KEY (idcategory) REFERENCES invcategory(idcategory);


--
-- TOC entry 2445 (class 2606 OID 18021)
-- Name: fk_invproductinstance_idproduct; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY invproductinstance
    ADD CONSTRAINT fk_invproductinstance_idproduct FOREIGN KEY (idproduct) REFERENCES invproduct(idproduct);


--
-- TOC entry 2446 (class 2606 OID 18026)
-- Name: fk_mbsitemestrutura_coditemfilho; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsitemestrutura
    ADD CONSTRAINT fk_mbsitemestrutura_coditemfilho FOREIGN KEY (coditemfilho) REFERENCES mbsitem(coditem);


--
-- TOC entry 2447 (class 2606 OID 18031)
-- Name: fk_mbsitemestrutura_coditempai; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsitemestrutura
    ADD CONSTRAINT fk_mbsitemestrutura_coditempai FOREIGN KEY (coditempai) REFERENCES mbsitem(coditem);


--
-- TOC entry 2448 (class 2606 OID 18036)
-- Name: fk_mbspessoa_cdidomain; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbspessoa
    ADD CONSTRAINT fk_mbspessoa_cdidomain FOREIGN KEY (cdidomain) REFERENCES admdomain(cdidomain);


--
-- TOC entry 2449 (class 2606 OID 18041)
-- Name: fk_mbspessoa_idcitybirth; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbspessoa
    ADD CONSTRAINT fk_mbspessoa_idcitybirth FOREIGN KEY (idcityplaceofbirth) REFERENCES geocity(idcity);


--
-- TOC entry 2450 (class 2606 OID 18046)
-- Name: fk_mbspessoa_idnationality; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbspessoa
    ADD CONSTRAINT fk_mbspessoa_idnationality FOREIGN KEY (idcountrynationality) REFERENCES geocountry(idcountry);


--
-- TOC entry 2451 (class 2606 OID 18051)
-- Name: fk_mbspessoa_relethnicity; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbspessoa
    ADD CONSTRAINT fk_mbspessoa_relethnicity FOREIGN KEY (relethnicity) REFERENCES mbsethnicity(idethnicity);


--
-- TOC entry 2453 (class 2606 OID 20053)
-- Name: fk_mbssmsmessage_cdidomain; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbssmsmessage
    ADD CONSTRAINT fk_mbssmsmessage_cdidomain FOREIGN KEY (cdidomain) REFERENCES admdomain(cdidomain);


--
-- TOC entry 2517 (class 2606 OID 20043)
-- Name: fk_mbssmstemplate_cdidomain; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbssmstemplate
    ADD CONSTRAINT fk_mbssmstemplate_cdidomain FOREIGN KEY (cdidomain) REFERENCES admdomain(cdidomain);


--
-- TOC entry 2454 (class 2606 OID 18056)
-- Name: fk_mbsvideoprogramassoc_cdlvideo; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsvideoprogramassoc
    ADD CONSTRAINT fk_mbsvideoprogramassoc_cdlvideo FOREIGN KEY (cdlvideo) REFERENCES mbsvideo(cdlvideo);


--
-- TOC entry 2455 (class 2606 OID 18061)
-- Name: fk_mbsvideoprogramassoc_codprogram; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbsvideoprogramassoc
    ADD CONSTRAINT fk_mbsvideoprogramassoc_codprogram FOREIGN KEY (codprogram) REFERENCES mbsvideoprogram(codprogram);


--
-- TOC entry 2456 (class 2606 OID 18066)
-- Name: fk_mbswallcontribution_cdlfather; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbswallcontribution
    ADD CONSTRAINT fk_mbswallcontribution_cdlfather FOREIGN KEY (cdlfather) REFERENCES mbswallcontribution(cdlwallcontribution);


--
-- TOC entry 2457 (class 2606 OID 18071)
-- Name: fk_mbswallcontribution_codusuario; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbswallcontribution
    ADD CONSTRAINT fk_mbswallcontribution_codusuario FOREIGN KEY (codusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2458 (class 2606 OID 18076)
-- Name: fk_mbswallcontributionassoc_cdlwallcontribution; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbswallcontributionassoc
    ADD CONSTRAINT fk_mbswallcontributionassoc_cdlwallcontribution FOREIGN KEY (cdlwallcontribution) REFERENCES mbswallcontribution(cdlwallcontribution);


--
-- TOC entry 2459 (class 2606 OID 18081)
-- Name: fk_mbswallcontributionassoc_codusuario; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbswallcontributionassoc
    ADD CONSTRAINT fk_mbswallcontributionassoc_codusuario FOREIGN KEY (codusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2460 (class 2606 OID 18086)
-- Name: fk_mrpplanningitem_coditem; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mrpplanningitem
    ADD CONSTRAINT fk_mrpplanningitem_coditem FOREIGN KEY (coditem) REFERENCES mbsitem(coditem);


--
-- TOC entry 2461 (class 2606 OID 18091)
-- Name: fk_mrpplanningitem_codplanning; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mrpplanningitem
    ADD CONSTRAINT fk_mrpplanningitem_codplanning FOREIGN KEY (codplanning) REFERENCES mrpplanning(codplanning);


--
-- TOC entry 2476 (class 2606 OID 18096)
-- Name: fk_ocorrencia_usuarioclosed; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_ocorrencia_usuarioclosed FOREIGN KEY (codusuarioclosed) REFERENCES admusuario(codusuario);


--
-- TOC entry 2503 (class 2606 OID 18101)
-- Name: fk_pedrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpedrecording
    ADD CONSTRAINT fk_pedrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2494 (class 2606 OID 18106)
-- Name: fk_pessoa_cdidomain; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofile
    ADD CONSTRAINT fk_pessoa_cdidomain FOREIGN KEY (cdidomain) REFERENCES admdomain(cdidomain);


--
-- TOC entry 2452 (class 2606 OID 18111)
-- Name: fk_pessoa_idcity; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY mbspessoa
    ADD CONSTRAINT fk_pessoa_idcity FOREIGN KEY (idcity) REFERENCES geocity(idcity);


--
-- TOC entry 2511 (class 2606 OID 18116)
-- Name: fk_sclrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedsclrecording
    ADD CONSTRAINT fk_sclrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2462 (class 2606 OID 18121)
-- Name: fk_tmedalert_cdlocorrencia; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedalert
    ADD CONSTRAINT fk_tmedalert_cdlocorrencia FOREIGN KEY (cdlocorrencia) REFERENCES tmedocorrencia(cdlocorrencia);


--
-- TOC entry 2463 (class 2606 OID 18126)
-- Name: fk_tmedalert_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedalert
    ADD CONSTRAINT fk_tmedalert_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2464 (class 2606 OID 18131)
-- Name: fk_tmedalert_codrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedalert
    ADD CONSTRAINT fk_tmedalert_codrecording FOREIGN KEY (codrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2465 (class 2606 OID 18136)
-- Name: fk_tmedalertvalue_cdlalert; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedalertvalue
    ADD CONSTRAINT fk_tmedalertvalue_cdlalert FOREIGN KEY (cdlalert) REFERENCES tmedalert(cdlalert);


--
-- TOC entry 2466 (class 2606 OID 18141)
-- Name: fk_tmedbancofrase_cdlcustomer; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedbancofrase
    ADD CONSTRAINT fk_tmedbancofrase_cdlcustomer FOREIGN KEY (cdlcustomer) REFERENCES admcustomer(cdlcustomer);


--
-- TOC entry 2467 (class 2606 OID 18146)
-- Name: fk_tmedbgrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedbglrecording
    ADD CONSTRAINT fk_tmedbgrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2468 (class 2606 OID 18151)
-- Name: fk_tmedbprrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedbprrecording
    ADD CONSTRAINT fk_tmedbprrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2469 (class 2606 OID 18156)
-- Name: fk_tmeddevice_codusuario; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmeddevice
    ADD CONSTRAINT fk_tmeddevice_codusuario FOREIGN KEY (codusuario) REFERENCES admusuario(codusuario);


--
-- TOC entry 2470 (class 2606 OID 18161)
-- Name: fk_tmeddicomrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmeddicomrecording
    ADD CONSTRAINT fk_tmeddicomrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2471 (class 2606 OID 18166)
-- Name: fk_tmedecgrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedecgrecording
    ADD CONSTRAINT fk_tmedecgrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2472 (class 2606 OID 18171)
-- Name: fk_tmedexam_cdlcustomer; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedexam
    ADD CONSTRAINT fk_tmedexam_cdlcustomer FOREIGN KEY (cdlcustomer) REFERENCES admcustomer(cdlcustomer);


--
-- TOC entry 2473 (class 2606 OID 18176)
-- Name: fk_tmedimagerecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedimagerecording
    ADD CONSTRAINT fk_tmedimagerecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2474 (class 2606 OID 18181)
-- Name: fk_tmedmedico_cdlpessoa; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedmedico
    ADD CONSTRAINT fk_tmedmedico_cdlpessoa FOREIGN KEY (cdlpessoa) REFERENCES mbspessoa(cdlpessoa);


--
-- TOC entry 2475 (class 2606 OID 18186)
-- Name: fk_tmedmedicoesrecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedmedicoesrecording
    ADD CONSTRAINT fk_tmedmedicoesrecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2477 (class 2606 OID 18191)
-- Name: fk_tmedocorrencia_cdlcustomer; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_cdlcustomer FOREIGN KEY (cdlcustomer) REFERENCES admcustomer(cdlcustomer);


--
-- TOC entry 2478 (class 2606 OID 18196)
-- Name: fk_tmedocorrencia_cdlfrase; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_cdlfrase FOREIGN KEY (cdlfrase) REFERENCES tmedbancofrase(cdlbancofrases);


--
-- TOC entry 2479 (class 2606 OID 18201)
-- Name: fk_tmedocorrencia_cdlmedicosolic; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_cdlmedicosolic FOREIGN KEY (cdlmedicosolic) REFERENCES tmedmedico(cdlmedico);


--
-- TOC entry 2480 (class 2606 OID 18206)
-- Name: fk_tmedocorrencia_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2481 (class 2606 OID 18211)
-- Name: fk_tmedocorrencia_cdlpatientvet; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_cdlpatientvet FOREIGN KEY (cdlpatientvet) REFERENCES tmedpatientvet(cdlpatientvet);


--
-- TOC entry 2482 (class 2606 OID 18216)
-- Name: fk_tmedocorrencia_codlocalexame; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_codlocalexame FOREIGN KEY (codlocalexame) REFERENCES admlocalatend(codlocal);


--
-- TOC entry 2483 (class 2606 OID 18221)
-- Name: fk_tmedocorrencia_codlocalmarcacao; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_codlocalmarcacao FOREIGN KEY (codlocalmarcacao) REFERENCES admlocalatend(codlocal);


--
-- TOC entry 2484 (class 2606 OID 18226)
-- Name: fk_tmedocorrencia_codusuariolock; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_codusuariolock FOREIGN KEY (codusuariolock) REFERENCES admusuario(codusuario);


--
-- TOC entry 2485 (class 2606 OID 18231)
-- Name: fk_tmedocorrencia_codusuariosolic; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_codusuariosolic FOREIGN KEY (codusuariosolic) REFERENCES admusuario(codusuario);


--
-- TOC entry 2486 (class 2606 OID 18236)
-- Name: fk_tmedocorrencia_codusuariovista; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_codusuariovista FOREIGN KEY (codusuariovista) REFERENCES admusuario(codusuario);


--
-- TOC entry 2487 (class 2606 OID 18241)
-- Name: fk_tmedocorrencia_idexam; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencia
    ADD CONSTRAINT fk_tmedocorrencia_idexam FOREIGN KEY (idexam) REFERENCES tmedexam(idexam);


--
-- TOC entry 2488 (class 2606 OID 18246)
-- Name: fk_tmedocorrencialaudo_cdlocorrencia; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencialaudo
    ADD CONSTRAINT fk_tmedocorrencialaudo_cdlocorrencia FOREIGN KEY (cdlocorrencia) REFERENCES tmedocorrencia(cdlocorrencia);


--
-- TOC entry 2489 (class 2606 OID 18251)
-- Name: fk_tmedocorrencialaudo_codusuariolaudo; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedocorrencialaudo
    ADD CONSTRAINT fk_tmedocorrencialaudo_codusuariolaudo FOREIGN KEY (codusuariolaudo) REFERENCES admusuario(codusuario);


--
-- TOC entry 2490 (class 2606 OID 18256)
-- Name: fk_tmedoxirecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedoxirecording
    ADD CONSTRAINT fk_tmedoxirecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2491 (class 2606 OID 18261)
-- Name: fk_tmedpaciente_cdlpessoa; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpaciente
    ADD CONSTRAINT fk_tmedpaciente_cdlpessoa FOREIGN KEY (cdlpessoa) REFERENCES mbspessoa(cdlpessoa);


--
-- TOC entry 2492 (class 2606 OID 18266)
-- Name: fk_tmedpatientdrugs_cdlpatient; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientdrugs
    ADD CONSTRAINT fk_tmedpatientdrugs_cdlpatient FOREIGN KEY (cdlpatient) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2493 (class 2606 OID 18271)
-- Name: fk_tmedpatienthistoric_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatienthistoric
    ADD CONSTRAINT fk_tmedpatienthistoric_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2495 (class 2606 OID 18276)
-- Name: fk_tmedpatientprofile_cdlpatient; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofile
    ADD CONSTRAINT fk_tmedpatientprofile_cdlpatient FOREIGN KEY (cdlpatient) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2496 (class 2606 OID 18281)
-- Name: fk_tmedpatientprofileassociation_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofileassociation
    ADD CONSTRAINT fk_tmedpatientprofileassociation_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2497 (class 2606 OID 18286)
-- Name: fk_tmedpatientprofileassociation_cdlprofile; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofileassociation
    ADD CONSTRAINT fk_tmedpatientprofileassociation_cdlprofile FOREIGN KEY (cdlprofile) REFERENCES tmedpatientprofile(cdlprofile);


--
-- TOC entry 2498 (class 2606 OID 18291)
-- Name: fk_tmedpatientprofilefield_cdlprofile; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofilefield
    ADD CONSTRAINT fk_tmedpatientprofilefield_cdlprofile FOREIGN KEY (cdlprofile) REFERENCES tmedpatientprofile(cdlprofile);


--
-- TOC entry 2499 (class 2606 OID 18296)
-- Name: fk_tmedpatientprofilefield_codprogram; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofilefield
    ADD CONSTRAINT fk_tmedpatientprofilefield_codprogram FOREIGN KEY (codprogram) REFERENCES mbsvideoprogram(codprogram);


--
-- TOC entry 2500 (class 2606 OID 18301)
-- Name: fk_tmedpatientprofileschedule_cdlprofilefield; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientprofileschedule
    ADD CONSTRAINT fk_tmedpatientprofileschedule_cdlprofilefield FOREIGN KEY (cdlprofilefield) REFERENCES tmedpatientprofilefield(cdlprofilefield);


--
-- TOC entry 2501 (class 2606 OID 18306)
-- Name: fk_tmedpatientsupportnetwork_cdlpatient; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientsupportnetwork
    ADD CONSTRAINT fk_tmedpatientsupportnetwork_cdlpatient FOREIGN KEY (cdlpatient) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2502 (class 2606 OID 18311)
-- Name: fk_tmedpatientvet_cdlcustomer; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedpatientvet
    ADD CONSTRAINT fk_tmedpatientvet_cdlcustomer FOREIGN KEY (cdlcustomer) REFERENCES admcustomer(cdlcustomer);


--
-- TOC entry 2504 (class 2606 OID 18316)
-- Name: fk_tmedprofilefieldrange_cdlprofilefield; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedprofilefieldrange
    ADD CONSTRAINT fk_tmedprofilefieldrange_cdlprofilefield FOREIGN KEY (cdlprofilefield) REFERENCES tmedpatientprofilefield(cdlprofilefield);


--
-- TOC entry 2507 (class 2606 OID 18321)
-- Name: fk_tmedprogramenrollment_cdlpaciente; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedprogramenrollment
    ADD CONSTRAINT fk_tmedprogramenrollment_cdlpaciente FOREIGN KEY (cdlpaciente) REFERENCES tmedpaciente(cdlpaciente);


--
-- TOC entry 2508 (class 2606 OID 18326)
-- Name: fk_tmedrecording_cdlocorrencia; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedrecording
    ADD CONSTRAINT fk_tmedrecording_cdlocorrencia FOREIGN KEY (cdlocorrencia) REFERENCES tmedocorrencia(cdlocorrencia);


--
-- TOC entry 2509 (class 2606 OID 18331)
-- Name: fk_tmedrecording_idexam; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedrecording
    ADD CONSTRAINT fk_tmedrecording_idexam FOREIGN KEY (idexam) REFERENCES tmedexam(idexam);


--
-- TOC entry 2510 (class 2606 OID 18336)
-- Name: fk_tmedrecording_sequel; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedrecording
    ADD CONSTRAINT fk_tmedrecording_sequel FOREIGN KEY (cdlrecordingsequel) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2512 (class 2606 OID 18341)
-- Name: fk_tmedvideorecording_cdlrecording; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedvideorecording
    ADD CONSTRAINT fk_tmedvideorecording_cdlrecording FOREIGN KEY (cdlrecording) REFERENCES tmedrecording(cdlrecording);


--
-- TOC entry 2506 (class 2606 OID 20222)
-- Name: fk_tpfieldrange_idprotocol; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedprofilefieldrange
    ADD CONSTRAINT fk_tpfieldrange_idprotocol FOREIGN KEY (idprotocol) REFERENCES homecprotocol(idprotocol);


--
-- TOC entry 2505 (class 2606 OID 20048)
-- Name: fk_tpfieldrange_idtemplate; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY tmedprofilefieldrange
    ADD CONSTRAINT fk_tpfieldrange_idtemplate FOREIGN KEY (idtemplate) REFERENCES mbssmstemplate(idtemplate);


--
-- TOC entry 2513 (class 2606 OID 18346)
-- Name: fk_vmeduserconnection_codusersource; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduserconnection
    ADD CONSTRAINT fk_vmeduserconnection_codusersource FOREIGN KEY (codusersource) REFERENCES vmeduser(coduser);


--
-- TOC entry 2514 (class 2606 OID 18351)
-- Name: fk_vmeduserconnection_codusertarget; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduserconnection
    ADD CONSTRAINT fk_vmeduserconnection_codusertarget FOREIGN KEY (codusertarget) REFERENCES vmeduser(coduser);


--
-- TOC entry 2515 (class 2606 OID 18356)
-- Name: fk_vmeduserfriendship_codusersource; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduserfriendship
    ADD CONSTRAINT fk_vmeduserfriendship_codusersource FOREIGN KEY (codusersource) REFERENCES vmeduser(coduser);


--
-- TOC entry 2516 (class 2606 OID 18361)
-- Name: fk_vmeduserfriendship_codusertarget; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY vmeduserfriendship
    ADD CONSTRAINT fk_vmeduserfriendship_codusertarget FOREIGN KEY (codusertarget) REFERENCES vmeduser(coduser);


-- Completed on 2013-09-25 10:44:36

--
-- PostgreSQL database dump complete
--

