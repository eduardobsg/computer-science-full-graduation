/*==============================================================*/
/* DBMS name:      PostgreSQL 7                                 */
/* Created on:     28/3/2005 16:10:24                           */
/*==============================================================*/

/*==============================================================*/
/* Parte II: criação                                            */
/* Criação das tabelas, índices e restrições                    */
/*==============================================================*/

/*==============================================================*/
/* Table: DEPTO                                                 */
/*==============================================================*/
create table DEPTO (
CODDEPTO             CHAR(5)              not null,
NOMEDEPTO            VARCHAR(40)          not null,
constraint PK_DEPTO primary key (CODDEPTO)
);

/*==============================================================*/
/* Index: DEPTO_PK                                              */
/*==============================================================*/
create unique index DEPTO_PK on DEPTO (
CODDEPTO
);

/*==============================================================*/
/* Table: DISCIPLINA                                            */
/*==============================================================*/
create table DISCIPLINA (
CODDEPTO             CHAR(5)              not null,
NUMDISC              INT4                 not null,
NOMEDISC             VARCHAR(40)          not null,
CREDITOSDISC         INT4                 not null,
constraint PK_DISCIPLINA primary key (CODDEPTO, NUMDISC)
);

/*==============================================================*/
/* Index: DISCIPLINA_PK                                         */
/*==============================================================*/
create unique index DISCIPLINA_PK on DISCIPLINA (
CODDEPTO,
NUMDISC
);

/*==============================================================*/
/* Index: RELATION_20_FK                                        */
/*==============================================================*/
create  index RELATION_20_FK on DISCIPLINA (
CODDEPTO
);

/*==============================================================*/
/* Table: HORARIO                                               */
/*==============================================================*/
create table HORARIO (
CODDEPTO             CHAR(5)              not null,
NUMDISC              INT4                 not null,
ANOSEM               INT4                 not null,
SIGLATUR             CHAR(2)              not null,
DIASEM               INT4                 not null,
HORAINICIO           INT4                 not null,
CODPRED              INT4                 null,
NUMSALA              INT4                 null,
NUMHORAS             INT4                 not null,
constraint PK_HORARIO primary key (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR, DIASEM, HORAINICIO)
);

/*==============================================================*/
/* Index: HORARIO_PK                                            */
/*==============================================================*/
create unique index HORARIO_PK on HORARIO (
CODDEPTO,
NUMDISC,
ANOSEM,
SIGLATUR,
DIASEM,
HORAINICIO
);

/*==============================================================*/
/* Index: RELATION_32_FK                                        */
/*==============================================================*/
create  index RELATION_32_FK on HORARIO (
CODDEPTO,
NUMDISC,
ANOSEM,
SIGLATUR
);

/*==============================================================*/
/* Index: RELATION_50_FK                                        */
/*==============================================================*/
create  index RELATION_50_FK on HORARIO (
CODPRED,
NUMSALA
);

/*==============================================================*/
/* Table: PREDIO                                                */
/*==============================================================*/
create table PREDIO (
CODPRED              INT4                 not null,
NOMEPRED             VARCHAR(40)          not null,
constraint PK_PREDIO primary key (CODPRED)
);

/*==============================================================*/
/* Index: PREDIO_PK                                             */
/*==============================================================*/
create unique index PREDIO_PK on PREDIO (
CODPRED
);

/*==============================================================*/
/* Table: PREREQ                                                */
/*==============================================================*/
create table PREREQ (
CODDEPTO             CHAR(5)              not null,
NUMDISC              INT4                 not null,
CODDEPTOPREREQ       CHAR(5)              not null,
NUMDISCPREREQ        INT4                 not null,
constraint PK_PREREQ primary key (CODDEPTOPREREQ, CODDEPTO, NUMDISC, NUMDISCPREREQ)
);

/*==============================================================*/
/* Index: PREREQ_PK                                             */
/*==============================================================*/
create unique index PREREQ_PK on PREREQ (
CODDEPTOPREREQ,
CODDEPTO,
NUMDISC,
NUMDISCPREREQ
);

/*==============================================================*/
/* Index: TEM_PRE_FK                                            */
/*==============================================================*/
create  index TEM_PRE_FK on PREREQ (
CODDEPTO,
NUMDISC
);

/*==============================================================*/
/* Index: EH_PRE_FK                                             */
/*==============================================================*/
create  index EH_PRE_FK on PREREQ (
CODDEPTOPREREQ,
NUMDISCPREREQ
);

/*==============================================================*/
/* Table: PROFESSOR                                             */
/*==============================================================*/
create table PROFESSOR (
CODPROF              INT4                 not null,
CODDEPTO             CHAR(5)              not null,
CODTIT               INT4                 null,
NOMEPROF             VARCHAR(40)          null,
constraint PK_PROFESSOR primary key (CODPROF)
);

/*==============================================================*/
/* Index: PROFESSOR_PK                                          */
/*==============================================================*/
create unique index PROFESSOR_PK on PROFESSOR (
CODPROF
);

/*==============================================================*/
/* Index: RELATION_56_FK                                        */
/*==============================================================*/
create  index RELATION_56_FK on PROFESSOR (
CODDEPTO
);

/*==============================================================*/
/* Index: RELATION_58_FK                                        */
/*==============================================================*/
create  index RELATION_58_FK on PROFESSOR (
CODTIT
);

/*==============================================================*/
/* Table: PROFTURMA                                             */
/*==============================================================*/
create table PROFTURMA (
CODDEPTO             CHAR(5)              not null,
NUMDISC              INT4                 not null,
ANOSEM               INT4                 not null,
SIGLATUR             CHAR(2)              not null,
CODPROF              INT4                 not null,
constraint PK_PROFTURMA primary key (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR, CODPROF)
);

/*==============================================================*/
/* Index: PROFTURMA_PK                                          */
/*==============================================================*/
create unique index PROFTURMA_PK on PROFTURMA (
CODDEPTO,
NUMDISC,
ANOSEM,
SIGLATUR,
CODPROF
);

/*==============================================================*/
/* Index: PROFTURMA_FK                                          */
/*==============================================================*/
create  index PROFTURMA_FK on PROFTURMA (
CODDEPTO,
NUMDISC,
ANOSEM,
SIGLATUR
);

/*==============================================================*/
/* Index: PROFTURMA2_FK                                         */
/*==============================================================*/
create  index PROFTURMA2_FK on PROFTURMA (
CODPROF
);

/*==============================================================*/
/* Table: SALA                                                  */
/*==============================================================*/
create table SALA (
CODPRED              INT4                 not null,
NUMSALA              INT4                 not null,
CAPACSALA            INT4                 null,
DESCRSALA            VARCHAR(40)          null,
constraint PK_SALA primary key (CODPRED, NUMSALA)
);

/*==============================================================*/
/* Index: SALA_PK                                               */
/*==============================================================*/
create unique index SALA_PK on SALA (
CODPRED,
NUMSALA
);

/*==============================================================*/
/* Index: RELATION_49_FK                                        */
/*==============================================================*/
create  index RELATION_49_FK on SALA (
CODPRED
);

/*==============================================================*/
/* Table: TITULACAO                                             */
/*==============================================================*/
create table TITULACAO (
CODTIT               INT4                 not null,
NOMETIT              VARCHAR(40)          not null,
constraint PK_TITULACAO primary key (CODTIT)
);

/*==============================================================*/
/* Index: TITULACAO_PK                                          */
/*==============================================================*/
create unique index TITULACAO_PK on TITULACAO (
CODTIT
);

/*==============================================================*/
/* Table: TURMA                                                 */
/*==============================================================*/
create table TURMA (
CODDEPTO             CHAR(5)              not null,
NUMDISC              INT4                 not null,
ANOSEM               INT4                 not null,
SIGLATUR             CHAR(2)              not null,
CAPACTUR             INT4                 null,
constraint PK_TURMA primary key (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR)
);

/*==============================================================*/
/* Index: TURMA_PK                                              */
/*==============================================================*/
create unique index TURMA_PK on TURMA (
CODDEPTO,
NUMDISC,
ANOSEM,
SIGLATUR
);

/*==============================================================*/
/* Index: RELATION_31_FK                                        */
/*==============================================================*/
create  index RELATION_31_FK on TURMA (
CODDEPTO,
NUMDISC
);

alter table DISCIPLINA
   add constraint FK_DISCIPLI_RELATION__DEPTO foreign key (CODDEPTO)
      references DEPTO (CODDEPTO)
      on delete restrict on update cascade;

alter table HORARIO
   add constraint FK_HORARIO_RELATION__TURMA foreign key (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR)
      references TURMA (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR)
      on delete restrict on update cascade;

alter table HORARIO
   add constraint FK_HORARIO_RELATION__SALA foreign key (CODPRED, NUMSALA)
      references SALA (CODPRED, NUMSALA)
      on delete restrict on update cascade;

alter table PREREQ
   add constraint FK_PREREQ_EH_PRE_DISCIPLI foreign key (CODDEPTOPREREQ, NUMDISCPREREQ)
      references DISCIPLINA (CODDEPTO, NUMDISC)
      on delete restrict on update cascade;

alter table PREREQ
   add constraint FK_PREREQ_TEM_PRE_DISCIPLI foreign key (CODDEPTO, NUMDISC)
      references DISCIPLINA (CODDEPTO, NUMDISC)
      on delete restrict on update cascade;

alter table PROFESSOR
   add constraint FK_PROFESSO_RELATION__DEPTO foreign key (CODDEPTO)
      references DEPTO (CODDEPTO)
      on delete restrict on update cascade;

alter table PROFESSOR
   add constraint FK_PROFESSO_RELATION__TITULACA foreign key (CODTIT)
      references TITULACAO (CODTIT)
      on delete restrict on update cascade;

alter table PROFTURMA
   add constraint FK_PROFTURM_PROFTURMA_TURMA foreign key (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR)
      references TURMA (CODDEPTO, NUMDISC, ANOSEM, SIGLATUR)
      on delete restrict on update cascade;

alter table PROFTURMA
   add constraint FK_PROFTURM_PROFTURMA_PROFESSO foreign key (CODPROF)
      references PROFESSOR (CODPROF)
      on delete restrict on update cascade;

alter table SALA
   add constraint FK_SALA_RELATION__PREDIO foreign key (CODPRED)
      references PREDIO (CODPRED)
      on delete restrict on update cascade;

alter table TURMA
   add constraint FK_TURMA_RELATION__DISCIPLI foreign key (CODDEPTO, NUMDISC)
      references DISCIPLINA (CODDEPTO, NUMDISC)
      on delete restrict on update cascade;
