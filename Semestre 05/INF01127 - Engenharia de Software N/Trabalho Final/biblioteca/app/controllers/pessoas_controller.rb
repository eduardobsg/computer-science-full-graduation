class PessoasController < ApplicationController
  # GET /pessoas
  # GET /pessoas.xml
  def index
    @pessoas = Pessoa.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @pessoas }
    end
  end

  # GET /pessoas/1
  # GET /pessoas/1.xml
  def show
    @pessoa = Pessoa.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @pessoa }
    end
  end

  # GET /pessoas/new
  # GET /pessoas/new.xml
  def new
    @pessoa = Pessoa.new
    @pessoaTipos = PessoaTipo.all    

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @pessoa }
    end
  end

  # GET /pessoas/1/edit
  def edit
    @pessoa = Pessoa.find(params[:id])
    @pessoaTipos = PessoaTipo.all
  end

  # POST /pessoas
  # POST /pessoas.xml
  def create
    @pessoa = Pessoa.new(params[:pessoa])

    respond_to do |format|
      if @pessoa.save
        format.html { redirect_to(@pessoa, :notice => 'Pessoa was successfully created.') }
        format.xml  { render :xml => @pessoa, :status => :created, :location => @pessoa }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @pessoa.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /pessoas/1
  # PUT /pessoas/1.xml
  def update
    @pessoa = Pessoa.find(params[:id])

    respond_to do |format|
      if @pessoa.update_attributes(params[:pessoa])
        format.html { redirect_to(@pessoa, :notice => 'Pessoa was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @pessoa.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /pessoas/1
  # DELETE /pessoas/1.xml
  def destroy
    @pessoa = Pessoa.find(params[:id])
    @pessoa.destroy

    respond_to do |format|
      format.html { redirect_to(pessoas_url) }
      format.xml  { head :ok }
    end
  end
end
